/*******************************************/
/*** DO NOT CHANGE ANYTHING IN THIS FILE ***/
/*******************************************/

// Defines a struct for modeling the missile
// .

#pragma once

#include "game_config.hxx"

#include <ge211.hxx>

#include <iostream>


/// We will represent positions as GE211 `Posn<float>`s, which we alias
/// with the type name `Position`. This is a struct that could be
/// defined like so:
///
///   struct Position
///   {
///       float x;   // pixel distance from left edge of window
///       float y;   // pixel distance from top edge of window
///   };
using Position = ge211::Posn<float>;


/// We will represent velocities as GE211 `Dims<float>`s, which we alias
/// with the type name `Velocity`. This is a struct that could be
/// defined like so:
///
///   struct Velocity
///   {
///       float width;   // horizontal rate of change (px/s)
///       float height;  // vertical rate of change (px/s)
///   };
using Velocity = ge211::Dims<float>;

/// We will represent blocks (the bricks and the paddle) as GE211
/// `Rect<int>`s, which we alias with the type name `Block`. This is a
/// struct that could be defined like so:
///
///   struct Block
///   {
///       int x;       // x coordinate of left side of rectangle
///       int y;       // y coordinate of top side of rectangle
///       int width;
///       int height;
///   };
using Block = ge211::Rect<int>;


/// This struct is used to represent the state of the missile
///
struct Eship
{
    //
    // CONSTRUCTOR
    //

    //
    ///
    Eship(Block const& eship, Game_config const&);

    //
    // MEMBER FUNCTIONS
    //

    bool hits_bottom(Game_config const&) const;



    bool hits_ship(Block const&) const;


    bool destroy_ship(std::vector<Block>& bricks) const;
    //
    // MEMBER VARIABLES
    //

    int radius;


    Position center;

    Velocity velocity;

    bool live;
};


struct Missile
{
    //
    // CONSTRUCTOR
    //

    Missile(Block const& uship, Game_config const&);

    //
    // MEMBER FUNCTIONS
    //

    Position top_left() const;

    /// Returns the state of the missile
    /// after `dt` seconds have passed,
    /// were it to move freely (without obstacles). Thus, the result is
    /// a new missile
    /// just like this one but whose position has been
    /// updated based on its current velocity and the given time
    /// interval `dt`. (This is an application of the equation relating
    /// distance to velocity and time: *Δd = v ⋅ Δt*.)
    ///
    /// This function is useful because the model's algorithm for
    /// collision detection involves speculatively moving the missile
    /// and
    /// checking where it would end up, before actually moving it.
    ///
    /// This can also be used to actually move it, via assignment:
    ///
    ///    missile
    /// = missile
    /// .next();
    ///
    Missile next(double dt) const;

    // These functions all perform collision detection by telling us whether
    // this missile
    // is *past* the given edge.

    /// Determines whether the missile
    /// extends past the top edge of the
    /// scene.
    bool hits_top(Game_config const&) const;

    bool hits_bottom(Game_config const&) const;


    /// Determines whether the missile
    /// 's bounding box intersects with the
    /// given ship.
    ///
    /// Intersection between a circle and a rectangle is tricky, so we
    /// will approximate it with the intersection of two rectangles.
    bool hits_ship(Block const&) const;

    /// Collision detection between the missile
    /// and the whole vector of
    /// bricks. If the missile
    /// collides with some brick then that brick is
    /// removed and the function returns true. (The missile
    /// may collide
    /// with more than one brick, but the function should return after
    /// the first collision is found.) If there is no collision then the
    /// function returns false.
    bool destroy_ship(std::vector<Block>& bricks) const;
    //
    // MEMBER VARIABLES
    //

    /// The radius of the missile
    /// .
    int radius;

    /// The position of the center of the missile
    /// .
    Position center;

    /// The velocity of the missile
    /// in pixels per tick.
    Velocity velocity;

    /// Whether the missile
    /// is moving freely (true) or stuck to the top of
    /// the paddle (false).
    bool live;
};

/// Compares two `Missile`s for equality. This may be useful for testing.
///
/// Two `Missile`s are equal if all their member variables are pairwise
/// equal.
bool
operator==(Missile const&, Missile const&);

/// Inequality for `Missile`s.
bool
operator!=(Missile const&, Missile const&);

/// Stream insertion (printing) for `Missile`. This can make your test
/// results easier to read.
std::ostream&
operator<<(std::ostream&, Missile const&);
