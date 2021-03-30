//
//  objects.cpp
//  SwiftBloks
//
//  Created by Benjamin Emde on 25.03.21.
//

#include "objects.hpp"
#include "define.h"
#include <iostream>

void tile::loop(float dt)
{
    rotate(false, dt * 100);
}

void tile::render()
{
    e.draw(*this);
}

void tile::load(float x, float y, int w, int h, SDL_Surface* pic)
{
    size.x = w;
    size.y = h;
    pos.x = x;
    pos.y = y;
    img = pic;
    
}

void tile::load(float x, float y, int w, int h, SDL_Surface* pic, vec4i quad_frame)
{
    size.x = w;
    size.y = h;
    pos.x = x;
    pos.y = y;
    img = pic;
    quad = quad_frame;
    isQuad = true;
}

void tile::move(float nx, float ny)
{
    pos.x += nx;
    pos.y += ny;
}

void tile::rotate(bool set, double rot)
{
    if (!set)
        rotation += rot;
    else
        rotation = rot;
}

vec2f tile::getPos()
{
    return pos;
}
vec2i tile::getSize()
{
    return size;
}

double tile::getRotation()
{
    return rotation;
}

void player::loop(float dt)
{
    movement(dt);
    
    if (e.isDown(SDLK_r))
        rotate(false, dt * 200);
    if (e.isDown(SDLK_a) and not e.isDown(SDLK_d))
        move(-100,0);
    elseif (e.isDown(SDLK_d) and not e.isDown(SDLK_a))
        move(100,0);
    if (e.isDown(SDLK_w) and not e.isDown(SDLK_s))
        move(0,-100);
    elseif (e.isDown(SDLK_s) and not e.isDown(SDLK_w))
        move(0,100);
}

void player::movement(float dt)
{
    pos.x += (vel.x * dt);
    pos.y += (vel.y * dt);
    vel.x *= pow(0.002 / (((phi.friction) / 1000) + 0.002), dt + phi.weight / 1000);
    vel.y *= pow(0.002 / (((phi.friction) / 1000) + 0.002), dt + phi.weight / 1000);
}

void player::render()
{
    e.draw(*this);
}

vec2f player::getVel()
{
    return vel;
}

void player::move(float nx, float ny)
{
    vel.x += nx;
    vel.y += ny;
}
