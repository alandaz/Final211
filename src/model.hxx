#pragma once


#include "game_config.hxx"
#include "missile.hxx"
#include <vector>
#include "ge211_time.hxx"


struct Model
{
    //consructor
    explicit Model(Game_config const& config = Game_config());

    void launch();

    void on_frame(double dt);

    void Timer();


    Game_config const config;


    std::vector<Block> eships1;
    std::vector<Block> eships2;
    std::vector<Block> eships3;




    // The position and dimensions of the paddle.
    Block uship;

    // The state of the ball. Much of the model's business actually
    // happens in there, so see ball.hxx for that.
    Missile missile;

    // A source of random “x-coord” values.
    ge211::Random_source<float> random_x;

    ge211::Random_source<float> pos_or_neg;



};