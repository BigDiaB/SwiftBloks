//
//  engine.cpp
//  SwiftBloks
//
//  Created by Benjamin Emde on 23.03.21.
//

#include "engine.hpp"
#include <iostream>

ENGINE::ENGINE(int w, int h)
{
#include "baseColors.h"
    
    DGcolor.white();
    WIDTH = w;
    HEIGHT = h;
    SDL_Init(SDL_INIT_EVERYTHING);
    SDL_CreateWindowAndRenderer(WIDTH, HEIGHT, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC, &window, &renderer);
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

void ENGINE::draw(float x, float y, SDL_Surface* surf, int xa, int ya, int w, int h)
{
    SDL_Rect quad;
    SDL_Rect body;
    
    quad.x = xa;
    quad.y = ya;
    quad.w = w;
    quad.h = h;
    
    body.x = x;
    body.y = y;
    body.w = w * SCALE_X;
    body.h = h * SCALE_Y;
    
    auto tex = SDL_CreateTextureFromSurface(renderer, surf);
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

tile ENGINE::newTile(float x, float y, SDL_Surface* pic, vec2i quad_pos)
{
    tile t;
    t.load(x, y, pic,quad_pos);
    if (tiles[index] == NULL)
        tiles[index] = &t;
    t.id = getID();
    return t;
}

tile ENGINE::newTile(float x, float y, SDL_Surface* pic)
{
    tile t;
    t.load(x, y, pic);
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

void ENGINE::test()
{
    for (int i = 0; i < index; i++)
    {
        draw(tiles[i]->getPos().x, tiles[i]->getPos().y, tiles[i]->img);
    }
}
