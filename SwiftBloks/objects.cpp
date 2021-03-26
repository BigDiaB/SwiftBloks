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
    pos.x += (vel.x * dt);
    pos.y += (vel.y * dt);
    vel.x *= pow(0.002, dt);
    vel.y *= pow(0.002, dt);
    if (isQuad)
        e.draw(*this);
    else
        e.draw(pos.x, pos.y, img);
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
    vel.x += nx;
    vel.y += ny;
}

vec2f tile::getPos()
{
    return pos;
}
vec2i tile::getSize()
{
    return size;
}
vec2f tile::getVel()
{
    return vel;
}
