#include "view.hxx"

using Color = ge211::Color;
using Sprite_set = ge211::Sprite_set;

// Use this to Make Game Larger
static int const scene_multiplier = 12;

View::View(Model const& model)
        : radius(0),
          target_pos{0,0},
          target_clicked(false),
          time(0),
          lives(0),
          shrink(1),
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

          game_timer()

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

//    if (!showMainMenu) {
//        initial_target_clicked=false;
//        if (!initial_target_clicked) {
//            set.add_sprite(target_sprite,
//                           center.left_by(model_.Dims().width)
//                                 .up_by(model_.Dims().height),5,target);
//
//            radius = target_sprite.dimensions().width * gamemode * 2;
//
//            target_pos = center.left_by(model_.Dims().width)
//                               .up_by(model_.Dims().height);
//
//            initial_target_clicked = true;
//        }
//    }

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
                             .up_by(scene_multiplier / 2), 9);

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


}

void
View::button_input(ge211::Sprite_set& set, View::Position mouse_posn)
{
    if (showMainMenu) {
        if (button_.easy_click(mouse_posn)) {
            set.add_sprite(game_board_sprite, {0, 0}, 4);
            showMainMenu = false;
            gamemode = 3;
        }

        if (button_.med_click(mouse_posn)) {
            set.add_sprite(game_board_sprite, {0, 0}, 4);
            showMainMenu = false;
            gamemode = 2;
        }

        if (button_.hard_click(mouse_posn)) {
            set.add_sprite(game_board_sprite, {0, 0}, 4);
            showMainMenu = false;
            gamemode = 1;
        }
    }

}

void
View::target_click(ge211::Sprite_set& set, View::Position mouse_posn)
{
//     target_pos = model_.random_spot(target_sprite.dimensions().width * gamemode,
//                                       initial_window_dimensions());

    ge211::Transform target = ge211::Transform{}
            .set_scale_x(0)
            .set_scale_y(0);

    if (gamemode == 3) {
        target = ge211::Transform{}
                .set_scale_x(3)
                .set_scale_y(3);
    } else if (gamemode == 2) {
        target = ge211::Transform{}
                .set_scale_x(2)
                .set_scale_y(2);
    } else if (gamemode == 1) {
        target = ge211::Transform{}
                .set_scale_x(1)
                .set_scale_y(1);
    }

    // Title Builder
    ge211::Text_sprite::Builder name_builder(font_info2);

    radius = target_sprite.dimensions().width * gamemode * 2;

    if (!showMainMenu) {

        if (target_clicked) {
            if (model_.hit_target(target_pos, mouse_posn, radius)) {
                target_pos = model_.random_spot(radius, initial_window_dimensions());
                target_clicked = true;
            }
        }

//        target = ge211::Transform{}
//                .set_scale_x(shrink)
//                .set_scale_y(shrink);

        set.add_sprite(target_sprite, target_pos, 5, target);

        int count = time;

        // Set Title color
        name_builder.color({0,255,250}) << count;

        // Updates the title_text sprite
        title_text.reconfigure(name_builder);

        set.add_sprite(title_text,{initial_window_dimensions().width - 100, 0}, 5);

    }

}








