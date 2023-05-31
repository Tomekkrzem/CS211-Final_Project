#include "view.hxx"
#include <iomanip>

using namespace std;

using Color = ge211::Color;
using Sprite_set = ge211::Sprite_set;

// Use this to Make Game Larger
static int const scene_multiplier = 12;

View::View(Model const& model)
        : radius(0),
          target_pos{620,320},
          target_clicked(false),
          time(0),
          lives(0),
          shrink(0),
          score(0),
          click_count(0),
          hit_count(0),
          accuracy(0),
          count_down(4),
          begin_count(false),
          differential(0),

          model_(model),
          button_(model_.Dims().width,model_.Dims().height,
                  {initial_window_dimensions().width / 2,
                   initial_window_dimensions().height / 2}),

          showMainMenu(true),

          menu_sprite(initial_window_dimensions(),{0,25,51}),
          title_text(),


          hard_sprite(button_.button_dims, {255,0,0}),

          medium_sprite(button_.button_dims, {255,255,0}),

          easy_sprite(button_.button_dims, {0,255,0}),

          h_hover_sprite(button_.button_dims, {153,0,0}),

          m_hover_sprite(button_.button_dims, {153,153,0}),

          e_hover_sprite(button_.button_dims, {0,153,0}),

          crosshair_sprite(scene_multiplier / 2 , {255, 255, 255}),

          game_board_sprite(initial_window_dimensions(),{0,0,0}),

          target_sprite(scene_multiplier * 2, {255,0,0}),

          game_timer(),

          game_over_screen(initial_window_dimensions(),{128,0,0}),

          score_sprite(),

          game_over_text(),

          back_button(button_.button_dims, {240,213,208}),

          back_hover(button_.button_dims, {216,147,134}),

          accuracy_sprite(),

          count_down_sprite(),

          heart1("6-pixel-heart-4.png"),

          heart2("6-pixel-heart-4.png"),

          heart3("6-pixel-heart-4.png"),

          back_to_menu_sprite()

{ }

void
View::draw(ge211::Sprite_set& set)
{
    // Title Builder
    ge211::Text_sprite::Builder name_builder(font_info);

    // Set Title color
    name_builder.color({0,255,250}) << "HITS";

    // Updates the title_text sprite
    title_text.reconfigure(name_builder);

    // Finds approximate center
    int x = initial_window_dimensions().width / 2;
    int y = initial_window_dimensions().height / 2;
    Position center = {x,y};

    if (showMainMenu) {
        set.add_sprite(menu_sprite, {0, 0});

        set.add_sprite(title_text,
                       {center.left_by(model_.Dims().width * 2.25)
                              .up_by(model_.Dims().height * 6)}, 2);

        set.add_sprite(easy_sprite, button_.e_button, 2);

        set.add_sprite(medium_sprite,button_.m_button, 2);

        set.add_sprite(hard_sprite,button_.h_button, 2);
    }

    if (!showMainMenu && model_.game_condition(time,lives)) {
        set.add_sprite(game_over_screen,{0,0},7);

        if (hit_count > click_count) {
            click_count = hit_count;
        }

        accuracy = (hit_count / click_count) * 100;

        double final_score = score - (click_count - hit_count) * 25;

        if (lives == 0) {
            final_score -= 300;
        } else if (lives == 1) {
            final_score -= 200;
        } else if (lives == 2) {
            final_score -= 100;
        }

        // Title Builder
        ge211::Text_sprite::Builder name_builder1(font_info2);
        ge211::Text_sprite::Builder name_builder2(font_info3);
        ge211::Text_sprite::Builder name_builder3(font_info2);

        // Set Title color
        name_builder1.color({238,232,170}) << "Score: " <<  final_score;
        name_builder2.color({240,213,208}) << "Game Over";
        name_builder3.color({238,232,170}) << "Accuracy: " << setprecision(3) << accuracy << "%";

        // Updates the title_text sprite
        score_sprite.reconfigure(name_builder1);
        game_over_text.reconfigure(name_builder2);
        accuracy_sprite.reconfigure(name_builder3);

        set.add_sprite(score_sprite,
                       {center.left_by(model_.Dims().width * 2)
                                .up_by(model_.Dims().height * 2.5)}, 8);

        set.add_sprite(accuracy_sprite,
                       {center.left_by(model_.Dims().width * 2)
                                .up_by(model_.Dims().height * 1.5)}, 8);

        set.add_sprite(game_over_text,
                       {center.left_by(model_.Dims().width * 4.25)
                                .up_by(model_.Dims().height * 6)}, 8);

        set.add_sprite(back_button,button_.back_button, 8);
    }


    if (begin_count && count_down > 0) {
        // Count Down Builder
        ge211::Text_sprite::Builder name_builder4(font_info4);

        int count = count_down;

        // Set Count Down color
        name_builder4.color({255,255,255}) << count;

        // Updates the count_down sprite
        count_down_sprite.reconfigure(name_builder4);

        set.add_sprite(count_down_sprite,
                       center.left_by(model_.Dims().width).up_by(model_.Dims().height * 4) , 6);
    }

    if (!showMainMenu && count_down <= 0) {

        ge211::Transform target = ge211::Transform{}
                .set_scale_x(gamemode)
                .set_scale_y(gamemode);

        if (gamemode == 3) {

            differential = gamemode - shrink * 0.5;

            target = ge211::Transform{}
                    .set_scale_x(differential)
                    .set_scale_y(differential);

            radius = target_sprite.dimensions().width * (differential) * 2;

        } else if (gamemode == 2) {

            differential = gamemode - shrink * 0.75;

            target = ge211::Transform{}
                    .set_scale_x(differential)
                    .set_scale_y(differential);

            radius = target_sprite.dimensions().width * (differential) * 2;
        } else if (gamemode == 1) {
            differential = gamemode - shrink;

            target = ge211::Transform{}
                    .set_scale_x(differential)
                    .set_scale_y(differential);

            radius = target_sprite.dimensions().width * (differential) * 2;
        }

        if (differential <= 0) {
            lives -= 1;
        }


        ge211::Transform heart = ge211::Transform{}
        .set_scale_y(0.03)
        .set_scale_x(0.03);

        if (lives == 0) {
            time = 0;
        } else if (lives == 1) {
            set.add_sprite(heart1,{0,0},5,heart);
        } else if (lives == 2) {
            set.add_sprite(heart1,{0,0},5,heart);
            set.add_sprite(heart2,{50,0},5,heart);
        } else if (lives == 3) {
            set.add_sprite(heart1,{0,0},5,heart);
            set.add_sprite(heart2,{50,0},5,heart);
            set.add_sprite(heart3,{100,0},5,heart);
        }



        set.add_sprite(target_sprite, target_pos, 6, target);
    }


}

View::Dimensions
View::initial_window_dimensions() const
{
    return scene_multiplier * model_.Dims();
}

void
View::draw_input(ge211::Sprite_set& set, ge211::Posn<int> mouse_posn)
{
    set.add_sprite(crosshair_sprite,
                   mouse_posn.left_by(scene_multiplier / 2)
                             .up_by(scene_multiplier / 2), 10);

    if (showMainMenu) {
        if (button_.easy_click(mouse_posn)) {
            set.add_sprite(e_hover_sprite,button_.e_button, 3);
        } else {
            set.add_sprite(easy_sprite,button_.e_button, 2);
        }

        if (button_.med_click(mouse_posn)) {
            set.add_sprite(m_hover_sprite,button_.m_button, 3);
        } else {
            set.add_sprite(medium_sprite,button_.m_button, 2);
        }

        if (button_.hard_click(mouse_posn)) {
            set.add_sprite(h_hover_sprite,button_.h_button, 3);
        } else {
            set.add_sprite(hard_sprite,button_.h_button, 2);
        }
    }

    if (!showMainMenu && model_.game_condition(time,lives)) {
        if (button_.back_click(mouse_posn)) {
            set.add_sprite(back_hover, button_.back_button, 9);
        } else {
            set.add_sprite(back_button,button_.back_button, 8);
        }
    }

}

void
View::button_input(ge211::Sprite_set& set, View::Position mouse_posn)
{
    if (showMainMenu) {
        if (button_.easy_click(mouse_posn)) {
            set.add_sprite(game_board_sprite, {0, 0}, 4);
            showMainMenu = false;
            gamemode = 3;
            begin_count = true;
        }

        if (button_.med_click(mouse_posn)) {
            set.add_sprite(game_board_sprite, {0, 0}, 4);
            showMainMenu = false;
            gamemode = 2;
            begin_count = true;
        }

        if (button_.hard_click(mouse_posn)) {
            set.add_sprite(game_board_sprite, {0, 0}, 4);
            showMainMenu = false;
            gamemode = 1;
            begin_count = true;
        }
    }


    if (!showMainMenu && model_.game_condition(time,lives)) {
        if (button_.back_click(mouse_posn)) {
            showMainMenu = true;
            gamemode = 0;
            target_clicked = false;
            score = 0;
            click_count = 0;
            hit_count = 0;
            accuracy = 0;
            count_down = 4;
            begin_count = false;
            shrink = 0;
        }
    }
}

void
View::target_click(ge211::Sprite_set& set, View::Position mouse_posn)
{
//    ge211::Transform target = ge211::Transform{}
//            .set_scale_x(0)
//            .set_scale_y(0);
//
//    if (gamemode == 3) {
//        target = ge211::Transform{}
//                .set_scale_x(3)
//                .set_scale_y(3);
//    } else if (gamemode == 2) {
//        target = ge211::Transform{}
//                .set_scale_x(2)
//                .set_scale_y(2);
//    } else if (gamemode == 1) {
//        target = ge211::Transform{}
//                .set_scale_x(1)
//                .set_scale_y(1);
//    }

    // Title Builder
    ge211::Text_sprite::Builder name_builder(font_info2);

    //radius = target_sprite.dimensions().width * gamemode * 2;

    if (!showMainMenu && count_down <= 0) {
        if (target_clicked) {
            if (model_.hit_target(target_pos, mouse_posn, radius) || (differential <= 0)) {
                target_pos = model_.random_spot(radius, initial_window_dimensions());
                target_clicked = true;
                score += 100;
                hit_count += 1;
                shrink = 0;
            }
        }

        //set.add_sprite(target_sprite, target_pos, 5, target);

        int count = time;

        // Set Title color
        name_builder.color({0,255,250}) << count;

        // Updates the title_text sprite
        title_text.reconfigure(name_builder);

        set.add_sprite(title_text,{initial_window_dimensions().width - 100, 0}, 5);

    }

}








