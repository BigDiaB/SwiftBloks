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
protected:
    vec2f pos;
    vec2i size;
    double rotation = 0;
public:
    int layer = 1;
    bool isQuad = false;
    int id;
    RGBAcolor color;
    SDL_Surface* img;
    vec4i quad;
    
    virtual void loop(float dt);
    virtual void render();
    void load(float x, float y, int w, int h, SDL_Surface* pic);
    void load(float x, float y, int w, int h, SDL_Surface* pic, vec4i quad_pos);
    void move(float nx, float ny);
    void rotate(bool set, double rot);
    
    vec2f getPos();
    vec2i getSize();
    vec2f getVel();
    double getRotation();
};

class player : public tile
{
    void movement(float dt);
public:
    physics phi;
    vec2f vel;
    void move(float nx, float ny); 
    vec2f getVel();
    int layer = 1;
    void loop(float dt) override;
    void render() override;
};
#endif /* objects_hpp */
