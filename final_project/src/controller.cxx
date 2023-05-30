#include "controller.hxx"


Controller::Controller(int size)
        : Controller(size,size)
{ }

Controller::Controller(int width, int height)
        : model_(width, height),
          view_(model_),
          cursor(0,0),
          click(0,0),
          rand_pos(0,0)

{}

void
Controller::draw(ge211::Sprite_set& set)
{
    view_.draw(set);
    view_.draw_input(set,cursor);
    view_.button_input(set,click);

    //if (model_.hit_target(view_.target_pos,click,view_.radius) && !model_.game_condition(view_.time,view_.lives)){
        //view_.target_pos = rand_pos;

    if (!model_.game_condition(view_.time,view_.lives)){
        view_.target_click(set,click);
    }
    //view_.target_click(set,click);

}

View::Dimensions
Controller::initial_window_dimensions() const
{
    return view_.initial_window_dimensions();
}

void Controller::on_mouse_move(ge211::Posn<int> pos)
{
    cursor = pos;
}

void
Controller::on_mouse_up(ge211::Mouse_button, ge211::Posn<int> pos)
{
    click = pos;

    if (!model_.game_condition(view_.time,view_.lives)){
        view_.click_count += 1;
    }


    if (!view_.target_clicked) {
        view_.time = 30;
        view_.lives = 3;
    }

    if (model_.hit_target(view_.target_pos, click, view_.radius)) {
        view_.target_clicked = true;
    }

}

void
Controller::on_frame(double dt)
{
    if (view_.begin_count) {
        view_.count_down -= dt * 0.75;
    }

    if (!model_.game_condition(view_.time,view_.lives) && view_.target_clicked) {
        view_.time -= dt;
        view_.shrink -= dt * 0.01;
    }
}