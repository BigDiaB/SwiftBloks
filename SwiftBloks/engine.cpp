//
//  engine.cpp
//  SwiftBloks
//
//  Created by Benjamin Emde on 23.03.21.
//
#include "define.h"
#include "engine.hpp"
#include <iostream>

float ENGINE::getDelta()
{
    return dt;
}

void ENGINE::tick()
    {
        unsigned int tick_time = SDL_GetTicks();
        dt = (tick_time - last_tick_time) * 0.001;
        last_tick_time = tick_time;
    }

ENGINE::ENGINE(char* name, int w, int h)
{
#include "baseColors.h"
    
    DGcolor.white();
    WIDTH = w;
    HEIGHT = h;
    SDL_Init(SDL_INIT_EVERYTHING);
    window = SDL_CreateWindow(name, SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, WIDTH, HEIGHT, 0);
    renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
}

void ENGINE::loop()
{
    while( SDL_PollEvent( &event ) ){
        switch( event.type ){
          case SDL_QUIT:
            running = false;
            break;

          case SDL_KEYUP:
            if (event.key.keysym.sym < 200)
                keys[event.key.keysym.sym] = 0;
              break;
                
          case SDL_KEYDOWN:
            if (event.key.keysym.sym < 200)
                keys[event.key.keysym.sym] = 1;
                break;

          default:
            break;
        }
      }
    SDL_RenderPresent(renderer);
    SDL_SetRenderDrawColor(renderer, BGcolor.r, BGcolor.g, BGcolor.b, BGcolor.a);
    SDL_RenderClear(renderer);
    SDL_SetRenderDrawColor(renderer, DGcolor.r, DGcolor.g, DGcolor.b, DGcolor.a);
}

bool ENGINE::isRunning()
{
    loop();
    if (isDown(SDLK_ESCAPE))
        running = false;
    if (!running)
    {
        SDL_DestroyWindow(window);
        SDL_DestroyRenderer(renderer);
        SDL_Quit();
    }
    tick();
    return running;
}

bool ENGINE::isDown(int key)
{
    return keys[key];
}

SDL_Surface* ENGINE::newImage(char* path)
{
    auto surface = IMG_Load(path);
    if (!surface)
    {
        std::cout << "FAILED TO DO STUFF\n";
        return NULL;
    }
    return surface;
}

void ENGINE::draw(float x, float y, SDL_Surface* surf)
{
    SDL_Rect rect;
    rect.x = x;
    rect.y = y;
    rect.w = surf->w * SCALE_X;
    rect.h = surf->h * SCALE_Y;
    auto tex = SDL_CreateTextureFromSurface(renderer, surf);
    SDL_RenderCopy(renderer, tex, nullptr, &rect);
    SDL_DestroyTexture(tex);
}

void ENGINE::draw(float x, float y, SDL_Surface* surf, float sx, float sy)
{
    SDL_Rect rect;
    rect.x = x;
    rect.y = y;
    rect.w = surf->w * sx;
    rect.h = surf->h * sy;
    auto tex = SDL_CreateTextureFromSurface(renderer, surf);
    SDL_RenderCopy(renderer, tex, nullptr, &rect);
    SDL_DestroyTexture(tex);
}

void ENGINE::draw(tile t)
{
    SDL_Rect quad;
    SDL_Rect body;
    body.w = t.getSize().x * SCALE_X;
    body.h = t.getSize().y * SCALE_Y;
    body.x = t.getPos().x;
    body.y = t.getPos().y;
    
    quad.x = t.quad.x;
    quad.y = t.quad.y;
    quad.w = t.quad.w;
    quad.h = t.quad.h;
    
    auto tex = SDL_CreateTextureFromSurface(renderer, t.img);
    SDL_RenderCopy(renderer, tex, &quad, &body);
    SDL_DestroyTexture(tex);
}

void ENGINE::draw(float x, float y, SDL_Surface* surf, int xa, int ya, int w, int h, float sx, float sy)
{
    SDL_Rect quad;
    SDL_Rect body;
    
    quad.x = xa;
    quad.y = ya;
    quad.w = w;
    quad.h = h;
    
    body.x = x;
    body.y = y;
    body.w = w * sx;
    body.h = h * sy;
    
    auto tex = SDL_CreateTextureFromSurface(renderer, surf);
    SDL_RenderCopy(renderer, tex, &quad, &body);
    SDL_DestroyTexture(tex);
}

void ENGINE::rect(bool fill, float x, float y, int w, int h)
{
    SDL_Rect rect;
    rect.x = x;
    rect.y = y;
    rect.w = w * SCALE_X;
    rect.h = h * SCALE_Y;
    
    if (fill)
        SDL_RenderFillRect(renderer, &rect);
    
    SDL_RenderDrawRect(renderer,&rect);
}

void ENGINE::rect(bool fill, float x, float y, int w, int h, float sx, float sy)
{
    SDL_Rect rect;
    rect.x = x;
    rect.y = y;
    rect.w = w * sx;
    rect.h = h * sy;
    
    if (fill)
        SDL_RenderFillRect(renderer, &rect);
    
    SDL_RenderDrawRect(renderer,&rect);
}
void ENGINE::setScale(float newX, float newY)
{
    if (newX != 0)
    SCALE_X = newX;
    if (newY != 0)
    SCALE_Y = newY;
}

void ENGINE::setIMGRGB(SDL_Surface* surf, RGBAcolor c)
{
    SDL_SetSurfaceColorMod(surf, c.r, c.g, c.b);
}

void ENGINE::setIMGALPHA(SDL_Surface *surf, int alpha)
{
    SDL_SetSurfaceAlphaMod(surf, alpha);
}

void ENGINE::setColor(RGBAcolor c)
{
    DGcolor.r = c.r;
    DGcolor.g = c.g;
    DGcolor.b = c.b;
    DGcolor.a = c.a;
    
}

void ENGINE::setBGcolor(RGBAcolor c)
{
    BGcolor.r = c.r;
    BGcolor.g = c.g;
    BGcolor.b = c.b;
    BGcolor.a = c.a;
}

tile ENGINE::newTile(float x, float y, SDL_Surface* pic, vec4i quad_frame)
{
    tile t;
    t.load(x, y, quad_frame.w, quad_frame.h, pic, quad_frame);
    if (tiles[index] == NULL)
        tiles[index] = &t;
    t.id = getID();
    return t;
}
tile ENGINE::newTile(float x, float y, SDL_Surface* pic, int xa, int ya, int w, int h)
{
    tile t;
    vec4i quad_frame;
    quad_frame.x = xa;
    quad_frame.y = ya;
    quad_frame.w = w;
    quad_frame.h = h;
    t.load(x, y, quad_frame.w, quad_frame.h, pic, quad_frame);
    if (tiles[index] == NULL)
        tiles[index] = &t;
    t.id = getID();
    return t;
}

tile ENGINE::newTile(float x, float y, int w, int h, SDL_Surface* pic)
{
    tile t;
    t.load(x, y, w, h, pic);
    if (tiles[index] == NULL)
        tiles[index] = &t;
    t.id = getID();
    return t;
}

int ENGINE::getID()
{
    retry:
    int id = random() % TILE_NUM;
    for (int i = 0; i < index; i++)
    {
        if (idblacklist[i] == id)
            goto retry;
    }
    idblacklist[index] = id;
    index++;
    return id;
}

vec4i ENGINE::calcQuad(int w, int h, int xid, int yid)
{
    vec4i quad;
    quad.x = (w + 1) * (xid - 1);
    quad.y = (h + 1) * (yid - 1);
    quad.w = w;
    quad.h = h;
    
    return quad;
}

vec4i ENGINE::calcQuad(int h, int xid, int yid)
{
    vec4i quad;
    quad.x = (h + 1) * (xid - 1);
    quad.y = (h + 1) * (yid - 1);
    quad.w = h;
    quad.h = h;
    
    return quad;
}

void ENGINE::debug(tile t)
{
    for (int i = 0; i < index; i++)
    {
        tiles[i]->loop(dt);
    }
}
