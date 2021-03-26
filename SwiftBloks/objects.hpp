//
//  objects.hpp
//  SwiftBloks
//
//  Created by Benjamin Emde on 25.03.21.
//

#ifndef objects_hpp
#define objects_hpp
#include "util.h"
#include <SDL2/SDL.h>

class tile
{
    vec2f pos;
    vec2f vel;
    vec2i size;
public:
    int id;
    RGBAcolor color;
    SDL_Surface* img;
    vec2i quad;
    
    void loop(int id);
    void load(float x, float y, SDL_Surface* pic);
    void load(float x, float y, SDL_Surface* pic, vec2i quad_pos);
    void move(float nx, float ny);
    
    vec2f getPos();
    vec2i getSize();
    vec2f getVel();
};

#endif /* objects_hpp */
