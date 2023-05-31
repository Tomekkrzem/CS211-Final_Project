#include "controller.hxx"

//Zero constructor
Controller::Controller(int size)
        : Controller(size,size)
{ }
//Main constructor
Controller::Controller(int width, int height)
        : model_(width, height),
          view_(model_),
          cursor(0,0),
          click(0,0)
{}

//Draws the view functions all together
void
Controller::draw(ge211::Sprite_set& set)
{
    view_.draw(set);
    view_.draw_input(set,cursor);
    view_.button_input(set,click);

    if (!model_.game_condition(view_.time,view_.lives)){
        view_.target_click(set,click);
    }
}

View::Dimensions
Controller::initial_window_dimensions() const
{
    return view_.initial_window_dimensions();
}

//Cursor follows the mouse
void Controller::on_mouse_move(ge211::Posn<int> pos)
{
    cursor = pos;
}

//When clicking
void
Controller::on_mouse_up(ge211::Mouse_button, ge211::Posn<int> pos)
{
    click = pos;

    if (!model_.game_condition(view_.time,view_.lives)){//count clicks
        view_.click_count += 1;
    }

    if (!view_.target_clicked) {//initialize game to 30 seconds and 3 lives
        view_.time = 30;
        view_.lives = 3;
    }

    if (model_.hit_target(view_.target_pos, click, view_.radius)) {//if target clicked
        view_.target_clicked = true;
    }

}

void
Controller::on_frame(double dt)
{
    if (view_.begin_count) {//beginning timer
        view_.count_down -= dt * 0.85;
    }

    if (!model_.game_condition(view_.time,view_.lives) && view_.target_clicked) {//start game
        view_.time -= dt;
    }

    if (view_.target_clicked && !model_.hit_target(view_.target_pos, click, view_.radius)) {//target shrinks
        view_.shrink += dt;
    }
}