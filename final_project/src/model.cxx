#include "model.hxx"

using namespace ge211;


Scene::Scene(Dimensions dims)
    : scene_dims(dims)
{
    if (dims.width < 2 || dims.height < 2) {
        throw Client_logic_error("Scene::Scene: dimensions too small");
    }

    if (dims.width > 120 || dims.height > 120) {
        throw Client_logic_error("Scene::Scene: dimensions too large");
    }
}

Scene::Dimensions
Scene::dimensions() const
{
    return scene_dims;
}

bool
Scene::good_position(Position pos) const
{
    return 0 <= pos.x && pos.x < scene_dims.width &&
           0 <= pos.y && pos.y < scene_dims.height;
}

void
Scene::bounds_check(Position pos) const
{
    if (!good_position(pos)) {
        throw Client_logic_error("Scene: position out of bounds");
    }
}

///--------------------------------------------------------------------------///

static int const scene_multiplier = 12;

Model::Model(int size)
        : Model(size,size)

{ }

Model::Model(int width, int height)
    : game_scene({width,height})
{ }

Model::Dimensions
Model::Dims() const
{
    return game_scene.dimensions();
}

Model::Position
Model::operator[](Position pos) const
{
    game_scene.bounds_check(pos);
    return pos;
}

Model::Position
Model::random_spot(int radius, Dimensions dims) const
{
    int width = dims.width;
    int height = dims.height;

    ge211::Random_source<int> x_rand(0, width - (2 * radius));
    ge211::Random_source<int> y_rand(0, height - (2 * radius));

    int x = x_rand.next();
    int y = y_rand.next();

    return {x,y};
}

int
Model::random_x(int radius, Dimensions dims) const
{
    int width = dims.width;

    ge211::Random_source<int> x_rand(0, width - (2 * radius));

    return x_rand.next();
}

int
Model::random_y(int radius, Dimensions dims) const
{
    int height = dims.width;

    ge211::Random_source<int> y_rand(0, height - (2 * radius));

    return y_rand.next();
}


bool
Model::game_over(int time, int lives) const
{
    bool result = false;

    if (time == 0) {
        result = true;
    } else if (lives == 0) {
        result = true;
    }

    return result;
}

bool Model::hit_target(Position target_pos, Position pos, int radius) const
{
    // int target_center_x = target_pos.x;
    // int target_center_y = target_pos.y;
    //
    // int click_center_x = pos.x;
    // int click_center_y = pos.y;
    //
    // int distance_squared = (target_center_x - click_center_x) * (target_center_x - click_center_x)
    //                        + (target_center_y - click_center_y) * (target_center_y - click_center_y);
    //
    // int radius_squared = radius * radius;
    //
    // return distance_squared <= radius_squared;

    bool result;

    Rectangle target(target_pos.x, target_pos.y,
                     radius / 2, radius / 2);

    // Cursor edges
    int r_cursor = pos.x + (scene_multiplier / 2);
    int l_cursor = pos.x - (scene_multiplier / 2);
    int t_cursor = pos.y - (scene_multiplier / 2);
    int b_cursor = pos.y + (scene_multiplier / 2);

    // Easy Button Edges
    int r_easy = target_pos.x + target.width;
    int l_easy = target_pos.x;
    int t_easy = target_pos.y;
    int b_easy = target_pos.y + target.height;

    bool cond1 = r_cursor < l_easy;
    bool cond2 = l_cursor > r_easy;
    bool cond3 = t_cursor > b_easy;
    bool cond4 = b_cursor < t_easy;

    if (cond1 || cond2 || cond3 || cond4){
        result = false;
    } else {
        result = true;
    }

    return result;


}



// void
// Model::target_animation(int time, int gamemode) const
// {
//     int max_time = 0;
//     switch (gamemode) {
//     // EASY_MODE:
//         max_time = 3000;  // 3 seconds
//         break;
//    // MEDIUM_MODE:
//         max_time = 2000;  // 2 seconds
//         break;
//     // HARD_MODE:
//         max_time = 1000;  // 1 second
//         break;
//     }
//     double scale_factor = 1.0 - (static_cast<double>(time) / max_time);
//
//     target_sprite.set_scale_x(scale_factor);
//     target_sprite.set_scale_y(scale_factor);
//
//
// }
///--------------------------------------------------------------------------///

Target::Target(int size)
        :Target(size,{size,size})
{}

Target::Target(int radius, Position pos)
        : target_pos(pos),
          target_radius(radius)
{}

///--------------------------------------------------------------------------///
Button::Button(int size)
        : Button(size,size,{size,size})
{}
Button::Button(int width, int height, Position pos)
        : e_button{pos.left_by(width * 1.5).up_by(height * 1.25)},
          m_button{pos.left_by(width * 1.5)},
          h_button{pos.left_by(width * 1.5).down_by(height * 1.25)},
          button_dims(width * 3,height),
          dims(width,height)
{};

bool
Button::button_click(Position pos, Position button_pos) const
{

    bool result;

    Rectangle button(button_pos.x, button_pos.y,
                       button_dims.width, button_dims.height);

    // Cursor edges
    int r_cursor = pos.x + (scene_multiplier / 2);
    int l_cursor = pos.x - (scene_multiplier / 2);
    int t_cursor = pos.y - (scene_multiplier / 2);
    int b_cursor = pos.y + (scene_multiplier / 2);

    // Easy Button Edges
    int r_easy = button_pos.x + button.width;
    int l_easy = button_pos.x;
    int t_easy = button_pos.y;
    int b_easy = button_pos.y + button.height;

    bool cond1 = r_cursor < l_easy;
    bool cond2 = l_cursor > r_easy;
    bool cond3 = t_cursor > b_easy;
    bool cond4 = b_cursor < t_easy;

    if (cond1 || cond2 || cond3 || cond4){
        result = false;
    } else {
        result = true;
    }

    return result;
}

bool
Button::easy_click(Position pos) const
{
    return (button_click(pos,e_button));
}

bool
Button::med_click(Position pos) const
{
    return (button_click(pos,m_button));
}

bool
Button::hard_click(Position pos) const
{
    return (button_click(pos,h_button));
}