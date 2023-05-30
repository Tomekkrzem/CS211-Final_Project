#pragma once

#include "model.hxx"

#include <string>

class View
{
public:
    /// View dimensions will use `int` coordinates.
    using Dimensions = ge211::Dims<int>;

    /// View positions will use `int` coordinates.
    using Position = ge211::Posn<int>;

    /// View rectangles will use `int` coordinates.
    using Rectangle = ge211::Rect<int>;

    explicit View(Model const& model);

    void draw(ge211::Sprite_set& set);

    Dimensions initial_window_dimensions() const;

    void draw_input(ge211::Sprite_set&, Position mouse_posn);

    void button_input(ge211::Sprite_set&, Position mouse_posn);

    void target_click(ge211::Sprite_set&, Position mouse_posn);

    int radius;

    Position target_pos;

    bool target_clicked;

    double time;

    int lives;

    long shrink;

    int score;

    double click_count;

    double hit_count;

    double accuracy;

    double count_down;

    bool begin_count;



private:
    //Model const& model_;
    Model model_;
    Button button_;

    bool showMainMenu;
    int gamemode = 0;
    //Position target_pos;

    ge211::Rectangle_sprite menu_sprite;

    ge211::Text_sprite title_text;
    ge211::Font font_info{"GamePlayedOutline-wrX8.ttf",
                          (initial_window_dimensions().height
                          / model_.Dims().height) * 20};

    // Main Button Sprites
    ge211::Rectangle_sprite hard_sprite;
    ge211::Rectangle_sprite medium_sprite;
    ge211::Rectangle_sprite easy_sprite;

    // Button Sprites darken when cursor hovers over them
    ge211::Rectangle_sprite h_hover_sprite;
    ge211::Rectangle_sprite m_hover_sprite;
    ge211::Rectangle_sprite e_hover_sprite;

    // Constant Cursor Sprite for Game
    ge211::Circle_sprite crosshair_sprite;

    // Main Game Background
    ge211::Rectangle_sprite game_board_sprite;

    // Target Sprite
    ge211::Circle_sprite target_sprite;

    ge211::Text_sprite game_timer;

    ge211::Font font_info2{"GamePlayedOutline-wrX8.ttf",
                          (initial_window_dimensions().height
                           / model_.Dims().height) * 5};

    ge211::Rectangle_sprite game_over_screen;
    ge211::Text_sprite score_sprite;

    ge211::Font font_info3{"GamePlayedOutline-wrX8.ttf",
                           (initial_window_dimensions().height
                            / model_.Dims().height) * 10};

    ge211::sprites::Text_sprite game_over_text;

    ge211::Rectangle_sprite back_button;

    ge211::Rectangle_sprite back_hover;

    ge211::Text_sprite accuracy_sprite;

    ge211::Text_sprite count_down_sprite;

    ge211::Font font_info4{"GamePlayedOutline-wrX8.ttf",
                           (initial_window_dimensions().height
                            / model_.Dims().height) * 30};
};
