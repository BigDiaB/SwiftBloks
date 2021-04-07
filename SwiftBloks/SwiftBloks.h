//
//  namespace.h
//  SwiftBloks
//
//  Created by Benjamin Emde on 31.03.21.
//

#pragma once

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_ttf.h>
#include <string>
#include <sstream>
#include <fstream>
#include <iostream>
#include "util.h"


struct Clock
{
    float dt = 0;
    unsigned int last_tick_time = 0;
    float getDelta()
    {
        return dt;
    }
    
    void tick()
    {
        unsigned int tick_time = SDL_GetTicks();
        dt = (tick_time - last_tick_time) * 0.001;
        last_tick_time = tick_time;
    }
    void wait(int time_in_seconds)
    {
        SDL_Delay(time_in_seconds * 1000);
    }
};

struct Window
{
    float SCALE_X = 10;
    float SCALE_Y = 10;
    int WIDTH;
    int HEIGHT;
    int keys[200];
    SDL_Window* window;
    SDL_Renderer* renderer;
    SDL_Event event;
};



namespace ENGINE_NAME {
int how_it_ran = 0;
struct Clock timer;
struct Window window;
bool running = 1;
int index = 0;
int idblacklist[ID_NUM];
TTF_Font* currentFont;
RGBAcolor TXTCcolor;
RGBAcolor DGcolor;
RGBAcolor BGcolor;



RGBAcolor tempcolor;

void start(char* name, int w, int h)
{
    TTF_Init();
    currentFont = TTF_OpenFont(DEFAULT_FONT, 16);
    TXTCcolor.white();
    DGcolor.white();
    window.WIDTH = w;
    window.HEIGHT = h;
    SDL_Init(SDL_INIT_EVERYTHING);
    window.window = SDL_CreateWindow(name, SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, window.WIDTH, window.HEIGHT, 0);
    window.renderer = SDL_CreateRenderer(window.window, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
}

bool isDown(int key)
{
    return window.keys[key];
}

char* int2charptr(float num)
{
    std::stringstream strs;
      strs << num;
      std::string temp_str = strs.str();
      char* char_type = (char*) temp_str.c_str();
    return char_type;
}


vec4i calcQuad(int w, int h, int xid, int yid)
{
    vec4i quad;
    quad.x = (w + 1) * (xid - 1);
    quad.y = (h + 1) * (yid - 1);
    quad.w = w;
    quad.h = h;
    
    return quad;
}

vec4i calcQuad(int h, int xid, int yid)
{
    vec4i quad;
    quad.x = (h + 1) * (xid - 1);
    quad.y = (h + 1) * (yid - 1);
    quad.w = h;
    quad.h = h;
    
    return quad;
}

bool isRunning()
{
    while( SDL_PollEvent( &window.event ) ){
        switch( window.event.type ){
            case SDL_QUIT:
                running = false;
                break;
                
            case SDL_KEYUP:
                if (window.event.key.keysym.sym < 200)
                    window.keys[window.event.key.keysym.sym] = 0;
                break;
                
            case SDL_KEYDOWN:
                if (window.event.key.keysym.sym < 200)
                    window.keys[window.event.key.keysym.sym] = 1;
                break;
                
            default:
                break;
        }
    }
    SDL_RenderPresent(window.renderer);
    SDL_SetRenderDrawColor(window.renderer, BGcolor.r, BGcolor.g, BGcolor.b, BGcolor.a);
    SDL_RenderClear(window.renderer);
    SDL_SetRenderDrawColor(window.renderer, DGcolor.r, DGcolor.g, DGcolor.b, DGcolor.a);
    
    if (isDown(SDLK_ESCAPE))
        running = false;
    if (!running)
    {
        SDL_DestroyWindow(window.window);
        SDL_DestroyRenderer(window.renderer);
        TTF_Quit();
        SDL_Quit();
    }
    timer.tick();
    return running;
}


vec2i getWindowDimensions()
{
    vec2i temp = { window.WIDTH, window.HEIGHT };
    return temp;
}

SDL_Surface* newImage(char* path)
{
    auto surface = IMG_Load(path);
    if (!surface)
    {
        std::cout << "WARNING: TEXTURE NOT FOUND\n          Reverting to default texture.....\n";
        return IMG_Load(MISSING_CUBE_TEXTURE_PATH);
    }
    return surface;
}

void draw(float x, float y, SDL_Surface* surf)
{
    if (surf != NULL)
    {
    SDL_Rect rect;
    rect.x = x;
    rect.y = y;
    rect.w = surf->w * window.SCALE_X;
    rect.h = surf->h * window.SCALE_Y;
    auto tex = SDL_CreateTextureFromSurface(window.renderer, surf);
    SDL_RenderCopy(window.renderer, tex, nullptr, &rect);
    SDL_DestroyTexture(tex);}
}

void draw(float x, float y, SDL_Surface* surf, float sx, float sy)
{
    SDL_Rect rect;
    rect.x = x;
    rect.y = y;
    rect.w = surf->w * sx;
    rect.h = surf->h * sy;
    auto tex = SDL_CreateTextureFromSurface(window.renderer, surf);
    SDL_RenderCopy(window.renderer, tex, nullptr, &rect);
    SDL_DestroyTexture(tex);
}

void draw(float x, float y, SDL_Surface* surf, vec4i t_quad)
{
    SDL_Rect body;
    body.w = surf->w * window.SCALE_X;
    body.h = surf->h * window.SCALE_Y;
    body.x = x;
    body.y = y;
    
    SDL_Rect quad;
    quad.x = t_quad.x;
    quad.y = t_quad.y;
    quad.w = t_quad.w;
    quad.h = t_quad.h;
    auto tex = SDL_CreateTextureFromSurface(window.renderer, surf);
    SDL_RenderCopyEx(window.renderer, tex, &quad, &body, NULL, nullptr, SDL_FLIP_NONE);
    SDL_DestroyTexture(tex);
}

void draw(float x, float y, SDL_Surface* surf, vec4i t_quad, float rot, float sx, float sy)
{
    
    auto tex = SDL_CreateTextureFromSurface(window.renderer, surf);
    
    SDL_Rect body;
    body.w = surf->w * sx;
    body.h = surf->h * sy;
    body.x = x;
    body.y = y;
    
    
    
    SDL_Rect quad;
    quad.x = t_quad.x;
    quad.y = t_quad.y;
    quad.w = t_quad.w;
    quad.h = t_quad.h;
    SDL_RenderCopyEx(window.renderer, tex, &quad, &body, rot, nullptr, SDL_FLIP_NONE);
    
    SDL_DestroyTexture(tex);
}

void draw(float x, float y, SDL_Surface* surf, float rot, float sx, float sy)
{
    
    auto tex = SDL_CreateTextureFromSurface(window.renderer, surf);
    
    SDL_Rect body;
    body.w = surf->w * sx;
    body.h = surf->h * sy;
    body.x = x;
    body.y = y;
    
    
    SDL_RenderCopyEx(window.renderer, tex, nullptr, &body, rot, nullptr, SDL_FLIP_NONE);
    
    SDL_DestroyTexture(tex);
}


void draw(float x, float y, SDL_Surface* surf, int xa, int ya, int w, int h, float sx, float sy)
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
    
    auto tex = SDL_CreateTextureFromSurface(window.renderer, surf);
    SDL_RenderCopy(window.renderer, tex, &quad, &body);
    SDL_DestroyTexture(tex);
}

void rect(bool fill, float x, float y, int w, int h)
{
    SDL_Rect rect;
    rect.x = x;
    rect.y = y;
    rect.w = w * window.SCALE_X;
    rect.h = h * window.SCALE_Y;
    
    if (fill)
        SDL_RenderFillRect(window.renderer, &rect);
    
    SDL_RenderDrawRect(window.renderer,&rect);
}

void rect(bool fill, float x, float y, int w, int h, float sx, float sy)
{
    SDL_Rect rect;
    rect.x = x;
    rect.y = y;
    rect.w = w * sx;
    rect.h = h * sy;
    
    if (fill)
        SDL_RenderFillRect(window.renderer, &rect);
    
    SDL_RenderDrawRect(window.renderer,&rect);
}
void setScale(float newX, float newY)
{
    if (newX != 0)
        window.SCALE_X = newX;
    if (newY != 0)
        window.SCALE_Y = newY;
}

void setIMGRGB(SDL_Surface* surf, RGBAcolor c)
{
    SDL_SetSurfaceColorMod(surf, c.r, c.g, c.b);
}

void setIMGALPHA(SDL_Surface *surf, int alpha)
{
    SDL_SetSurfaceAlphaMod(surf, alpha);
}

void setColor(RGBAcolor c)
{
    DGcolor.r = c.r;
    DGcolor.g = c.g;
    DGcolor.b = c.b;
    DGcolor.a = c.a;
    
}

void setBGcolor(RGBAcolor c)
{
    BGcolor.r = c.r;
    BGcolor.g = c.g;
    BGcolor.b = c.b;
    BGcolor.a = c.a;
}

void newFont(int size)
{
    if (currentFont == NULL)
        currentFont = TTF_OpenFont(DEFAULT_FONT, size);
    else
        std::cerr << "DEFAULT FONT ALREADY CREATED" << std::endl;
}

void newFont(char* path, int size)
{
    if (currentFont == NULL)
        currentFont = TTF_OpenFont(path, size);
    else
        std::cerr << "DEFAULT FONT ALREADY CREATED" << std::endl;
}

void changeFont(TTF_Font *newFont)
{
    TTF_CloseFont(currentFont);
    currentFont = newFont;
}

void changeTextColor(int r, int g, int b, int a)
{
    TXTCcolor.r = r;
    TXTCcolor.g = g;
    TXTCcolor.b = b;
    TXTCcolor.a = a;
}


void write(float x, float y, char* text)
{
    SDL_Color c;
    c.r = TXTCcolor.r;
    c.g = TXTCcolor.g;
    c.b = TXTCcolor.b;
    c.a = TXTCcolor.a;
    
    if (currentFont != NULL)
        draw(x, y, TTF_RenderText_Solid(currentFont, text, c));
}

void write(float x, float y, RGBAcolor bg, char* text, RGBAcolor dc)
{
    SDL_Color c;
    c.r = dc.r;
    c.g = dc.g;
    c.b = dc.b;
    c.a = dc.a;
    
    SDL_Color g;
    g.r = bg.r;
    g.g = bg.g;
    g.b = bg.g;
    g.a = bg.a;
    
    draw(x, y, TTF_RenderText_Shaded(currentFont, text, c, g));
}



void write(float x, float y, char* text, RGBAcolor dc)
{
    SDL_Color c;
    c.r = dc.r;
    c.g = dc.g;
    c.b = dc.b;
    c.a = dc.a;
    
    draw(x, y, TTF_RenderText_Solid(currentFont, text, c));
}

void write(float x, float y, RGBAcolor bg, char* text)
{
    SDL_Color c;
    c.r = TXTCcolor.r;
    c.g = TXTCcolor.g;
    c.b = TXTCcolor.b;
    c.a = TXTCcolor.a;
    
    SDL_Color g;
    g.r = bg.r;
    g.g = bg.g;
    g.b = bg.g;
    g.a = bg.a;
    
    
    draw(x, y, TTF_RenderText_Shaded(currentFont, text, c, g));
}

void write(float x, float y, float num)
{
    SDL_Color c;
    c.r = TXTCcolor.r;
    c.g = TXTCcolor.g;
    c.b = TXTCcolor.b;
    c.a = TXTCcolor.a;
    
    
    
    
    
    if (currentFont != NULL)
        draw(x, y, TTF_RenderText_Solid(currentFont, int2charptr(num), c));
}

}
