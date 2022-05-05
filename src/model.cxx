// YOU DEFINITELY NEED TO MODIFY THIS FILE.

#include "model.hxx"
#include "ge211_time.hxx"


Model::Model(Game_config const& config)
        : config(config),
          uship(Block::from_top_left(config.uship_top_left_0(),
                                      config.uship_dims)),
          missile(uship,config),
          random_x(config.side_margin, config.scene_dims.width - config
          .side_margin),
          //1 = pos | 2 = neg
          pos_or_neg(1,2)
{
    //using Time =ge211::Timer;

    //We should set up the number of each type of ship in this. Then store it
    // into seperate vectors.Then in the view, we use the timer to see when
    // to place them and where

    float xcoord1 = config.side_margin;
    float ycoord1 = config.top_margin;

    for (int i = 0; i<config.eship1total; i++){
        Block epic1 = Block(xcoord1,ycoord1, config.eship1_dims().width, config
        .eship1_dims().height);
        xcoord1 = random_x(config.side_margin, config.scene_dims.width-config
        .side_margin);
        eships1.push_back(epic1);
    }

    float xcoord2 = config.side_margin;
    float ycoord2 = config.top_margin;

    for (int i = 0; i<config.eship2total; i++){
        Block epic2 = Block(xcoord2,ycoord2, config.eship2_dims().width, config
        .eship2_dims().height);
        xcoord2 = random_x(config.side_margin, config.scene_dims.width-config
            .side_margin);
        eships2.push_back(epic2);
}
    float xcoord3 = config.side_margin;
    float ycoord3 = config.top_margin;

    for (int i = 0; i<config.eship3total; i++){
        Block epic3 = Block(xcoord3,ycoord3, config.eship3_dims().width, config
                .eship3_dims().height);
        xcoord2 = random_x(config.side_margin, config.scene_dims.width-config
                .side_margin);
        eships3.push_back(epic3);
    }
}


// Freebie.
void
Model::launch()
{
    missile.live = true;
}



void
Model::on_frame(double dt)
{
    if (missile.live == false){
        return ;
    }

    else if(missile.next(dt).hits_top(config)){
        missile.live = false;
        missile.velocity.width = config.missile_velocity_0.width;
        missile.velocity.height = config.missile_velocity_0.height;
        //missile = ;
        return ;
    }


    missile = missile.next(dt);
}

//creating a Timer

void
Model::Timer()
{
    constexpr unsigned TPS = 30; //ticks per seconds
    const sf::Time     timePerUpdate = sf::seconds(1.0f / float(TPS));
    unsigned ticks = 0;

    sf::Clock timer;
    auto lastTime = sf::Time::Zero;
    auto lag      = sf::Time::Zero;

        //Get times
        auto time = timer.getElapsedTime();
        auto elapsed = time - lastTime;
        lastTime = time;
        lag += elapsed;

        //Real time update
        Model.handleInput();
        Model.update(elapsed);
        counter.update();

        //Fixed time update
        while (lag >= timePerUpdate)
        {
            ticks++;
            lag -= timePerUpdate;
            state.fixedUpdate(elapsed);
        }

        //Render
        m_window.clear();
        state.render(m_window);
        counter.draw(m_window);
        m_window.display();


        //Handle window events
        handleEvent();
        tryPop();
    }
}