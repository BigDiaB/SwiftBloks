//
//  objects.cpp
//  SwiftBloks
//
//  Created by Benjamin Emde on 25.03.21.
//

#include "objects.hpp"

void tile::loop(int id)
{
    
}
void tile::load(float x, float y, SDL_Surface* pic)
{
    pos.x = x;
    pos.y = y;
    img = pic;
}

void tile::load(float x, float y, SDL_Surface* pic, vec2i quad_pos)
{
    pos.x = x;
    pos.y = y;
    img = pic;
    quad = quad_pos;
}

void tile::move(float nx, float ny)
{
    pos.x += nx;
    pos.y += ny;
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
