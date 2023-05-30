#pragma once

#include <ge211.hxx>


class Scene
{
public:

    using Dimensions = ge211::Dims<int>;

    using Position = ge211::Posn<int>;

    using Rectangle = ge211::Rect<int>;

    bool good_position(Position) const;

    void bounds_check(Position) const;

private:

    Dimensions scene_dims;

public:

    explicit Scene(Dimensions dims);

    Dimensions dimensions() const;
};




class Model
{
public:
    using Dimensions = ge211::Dims<int>;

    using Position = ge211::Posn<int>;

    using Rectangle = ge211::Rect<int>;

    explicit Model(int size = 100);

    Model(int width, int height);

    Dimensions Dims() const;

    Position operator[](Position) const;

    Position random_spot(int radius, Dimensions dims) const;

    bool hit_target(Position,Position, int radius) const;

    void target_animation(double time, int gamemode) const;

    bool game_condition (double time, int lives);



private:
    Scene game_scene;
    bool game_over;
};




class Target
{
public:
    using Dimensions = ge211::Dims<int>;

    using Position = ge211::Posn<int>;

    using Rectangle = ge211::Rect<int>;

    explicit Target (int size = 0);

    Target(int radius, Position pos);

//    Target next_target();

    bool hit_target(Position,Position, int radius) const;

    Position target_pos;
    int target_radius;

private:
};




class Button
{
public:
    using Dimensions = ge211::Dims<int>;

    using Position = ge211::Posn<int>;

    using Rectangle = ge211::Rect<int>;

    explicit Button (int size = 0);

    Button(int width, int height, Position pos);

    bool button_click(Position, Position) const;

    bool easy_click(Position) const;

    bool med_click(Position) const;

    bool hard_click(Position) const;

    bool back_click(Position) const;

    Position e_button;
    Position m_button;
    Position h_button;
    Position back_button;
    Dimensions button_dims;

private:
    Dimensions dims;
};