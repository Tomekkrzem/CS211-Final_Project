#include "view.hxx"

using Color = ge211::Color;
using Sprite_set = ge211::Sprite_set;

// Use this to Make Game Larger
static int const scene_multiplier = 12;

View::View(Model const& model)
        : target_pos{0,0},
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

          crosshair_sprite(scene_multiplier / 2 ,
                           {255, 255, 255}),

          game_board_sprite(initial_window_dimensions(),{0,0,0}),


          target_sprite("target_.png"),

          initial_target_clicked(false)


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
    int y =initial_window_dimensions().height / 2;
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


    ge211::Transform target = ge211::Transform{}
            .set_scale_x(0)
            .set_scale_y(0);

    if (gamemode == 1) {
         target = ge211::Transform{}
                .set_scale_x(0.6)
                .set_scale_y(0.6);
    } else if (gamemode == 2) {
        target = ge211::Transform{}
                .set_scale_x(0.4)
                .set_scale_y(0.4);
    } else if (gamemode == 3) {
        target = ge211::Transform{}
                .set_scale_x(0.2)
                .set_scale_y(0.2);
    }


    if (!showMainMenu) {
        initial_target_clicked=false;
        if (!initial_target_clicked) {
            set.add_sprite(target_sprite,
                           center.left_by(model_.Dims().width)
                                 .up_by(model_.Dims().height),5,target);

            radius = target_sprite.dimensions().width * 0.8;

            target_pos = center.left_by(model_.Dims().width)
                               .up_by(model_.Dims().height);

            initial_target_clicked = true;
        }
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
            gamemode = 1;
        }

        if (button_.med_click(mouse_posn)) {
            set.add_sprite(game_board_sprite, {0, 0}, 4);
            showMainMenu = false;
            gamemode = 2;
        }

        if (button_.hard_click(mouse_posn)) {
            set.add_sprite(game_board_sprite, {0, 0}, 4);
            showMainMenu = false;
            gamemode = 3;
        }
    }

}

void
View::target_click(ge211::Sprite_set& set, View::Position mouse_posn)
{
    // target_pos = model_.random_spot(target_sprite.dimensions().width,
    //                                   initial_window_dimensions());

    ge211::Transform target = ge211::Transform{}
            .set_scale_x(0)
            .set_scale_y(0);

    if (gamemode == 1) {
        target = ge211::Transform{}
                .set_scale_x(0.6)
                .set_scale_y(0.6);
    } else if (gamemode == 2) {
        target = ge211::Transform{}
                .set_scale_x(0.4)
                .set_scale_y(0.4);
    } else if (gamemode == 3) {
        target = ge211::Transform{}
                .set_scale_x(0.2)
                .set_scale_y(0.2);
    }

    if (!showMainMenu && initial_target_clicked) {
        set.add_sprite(target_sprite, {100,100},5,target);
    }
}








