#include "model.hxx"
#include <catch.hxx>

TEST_CASE("example test (TODO: replace this)")
{
    CHECK(1 + 1 == 2);
}

TEST_CASE("Button Click Test")
{
    Model model_(100,100);

    ge211::Posn<int> pos = {0,0};

    // CHECK_FALSE(model_.easy_click(pos));
    //
    // CHECK_FALSE(model_.med_click(pos));
    //
    // CHECK_FALSE(model_.hard_click(pos));

    CHECK_FALSE(model_.random_spot(6,model_.Dims()).x == 0);
    CHECK_FALSE(model_.random_spot(6,model_.Dims()).y == 0);
}

TEST_CASE("Game Over")
{
    Model model_(100,100);

    int time = 10;
    int lives = 3;

    CHECK_FALSE(model_.game_condition(time,lives));

    lives = 0;

    CHECK(model_.game_condition(time,lives));

    lives = 3;
    time = 0;

    CHECK(model_.game_condition(time,lives));

}