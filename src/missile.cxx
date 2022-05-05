// YOU DEFINITELY NEED TO MODIFY THIS FILE.

#include "missile.hxx"
#include "game_config.hxx"

// Computes where the missile should be when it's stuck to the paddle:
// centered above it, 1 pixel up.
static Position
above_block(
        Block const& block,
        Game_config const& config)
{
    Position topleft = ge211::Posn<float>(block.top_left());
    Position p2 = Position(topleft.right_by(((block.width)/2)));
    Position p3 = Position(topleft.up_by(1 + config.missile_radius));
    Position result = Position (p2.x, p3.y);
    return result;
}

// It won't compile without this, so you get it for free.

Missile::Missile(Block const& uship, Game_config const& config)
        :radius(config.missile_radius),
          center(above_block(uship, config)),
          velocity(Velocity(config.missile_velocity_0)),
          live(false)
{ }
bool
Missile::hits_top(Game_config const&) const
{
    Position ballcenter = Missile::center;
    int radius = Missile::radius;

    Position p2 = Position(ballcenter.up_by(radius));
    int top = p2.y;

    if (top < 0 ){
        return true;
    }
    else{
        return false;
    }}

bool
Missile::hits_bottom(Game_config const& config) const
{
    Position ballcenter = Missile::center;
    int radius = Missile::radius;

    Position p2 = Position(ballcenter.down_by(radius));
    int bottom = p2.y;
    int bottom_scene = (config.scene_dims.height);

    if (bottom > bottom_scene){
        return true;
    }
    else{
        return false;
    }}


//detecting where the missile is after it
Missile
Missile::next(double dt) const
{
    Missile result(*this);
    int missilexv = Missile::velocity.width;
    int missileyv = Missile::velocity.height;
    Position epic = Missile::center;

    Position p2 = Position(epic.right_by(missilexv * dt));
    Position p3 = Position(epic.up_by(-missileyv * dt));

    Position end = Position(p2.x,p3.y);

    result.center = end;

    return result;
}

//IF HITS A ENEMY SHIP WITH MISSILE
bool
Missile
::hits_ship(Block const& block) const
{
    Position missilecenter = Missile::center;
    int radius = Missile::radius;
    Position missileright = Position(missilecenter.right_by(radius));
    Position missileleft = Position(missilecenter.left_by(radius));
    Position missileup = Position(missilecenter.up_by(radius));
    Position missiledown = Position(missilecenter.down_by(radius));

    Position eshipcenter = ge211::Posn<float>(block.center());
    int eshipwidth = block.width/2;
    int eshipheight = block.height/2;
    Position eshipright = Position(eshipcenter.right_by(eshipwidth));
    Position eshipleft = Position(eshipcenter.left_by(eshipwidth));
    Position eshipup = Position(eshipcenter.up_by(eshipheight));
    Position eshipdown = Position(eshipcenter.down_by(eshipheight));

    if (missileright.x < eshipleft.x || eshipright.x < missileleft.x ||
    missiledown.y <eshipup.y || eshipdown.y < missileup.y){
        return false;
    }
    else{
        return true;
    }

}


bool
Missile::destroy_ship(std::vector<Block>& eship) const
{
    size_t count = 0;
    for (Block x : eship){

        if (hits_ship(x)){
            std::swap(eship.at(count),eship.back());
            eship.pop_back();

            return true;
        }
        count = count + 1;
    }
    return false;
}

bool
operator==(Missile const& a, Missile const& b)
{
    if (a.radius == b.radius && a.center == b.center && a.velocity == b.velocity && a.live == b.live){
        return true;
    }
    return false;
}

bool
operator!=(Missile const& a, Missile const& b)
{
    return !(a == b);
}

std::ostream&
operator<<(std::ostream&, Missile const&);
