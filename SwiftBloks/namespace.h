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
#include <iostream>
#include "define.h"
#include "util.h"
#include "objects.hpp"

struct tile_layers
{
    tile* tiles[TILE_NUM];
};

struct clock
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
};

struct renderer
{
    tile_layers render_space[NUM_LAYERS];
    TTF_Font* currentFont;
    RGBAcolor TXTCcolor;
    RGBAcolor DGcolor;
    RGBAcolor BGcolor;
    void renderMe(tile* t)
    {
        for (int i = 0; i < TILE_NUM; i++)
        {
            if (render_space[t->layer].tiles[i] == NULL)
            {
                render_space[t->layer].tiles[i] = t;
                break;
            }
        }
    }
    
    void destroyMe(tile* t)
    {
        for (int i = 0; i < TILE_NUM; i++)
        {
            if (t->id == render_space[t->layer].tiles[i]->id)
                render_space[t->layer].tiles[i] = NULL;
        }
    }
    
    void renderMe(player* t)
    {
        for (int i = 0; i < TILE_NUM; i++)
        {
            if (render_space[t->layer].tiles[i] == NULL)
            {
                render_space[t->layer].tiles[i] = t;
                break;
            }
        }
    }
    
    void destroyMe(player* t)
    {
        for (int i = 0; i < TILE_NUM; i++)
        {
            if (t->id == render_space[t->layer].tiles[i]->id)
                render_space[t->layer].tiles[i] = NULL;
        }
    }
    
    void render()
    {
        for (int l = 0; l < NUM_LAYERS; l++)
        {
            for (int g = 0; g < TILE_NUM; g++)
            {
                if (render_space[l].tiles[g] != NULL)
                {
                    render_space[l].tiles[g]->render();
                }
            }
        }
    }
    
};

struct looper
{
    tile* loop_space[TILE_NUM];
    void loopMe(tile* t)
    {
        for (int i = 0; i < TILE_NUM; i++)
        {
            if (loop_space[i] == NULL)
            {
                loop_space[i] = t;
                break;
            }
        }
    }
    
    void stopme(tile* t)
    {
        for (int i = 0; i < TILE_NUM; i++)
        {
            if (t->id == loop_space[i]->id)
                loop_space[i] = NULL;
        }
    }
    
    void loopMe(player* t)
    {
        for (int i = 0; i < TILE_NUM; i++)
        {
            if (loop_space[i] == NULL)
            {
                loop_space[i] = t;
                break;
            }
        }
    }
    
    void stopMe(player* t)
    {
        for (int i = 0; i < TILE_NUM; i++)
        {
            if (t->id == loop_space[i]->id)
                loop_space[i] = NULL;
        }
    }
    
    void loop(float dt)
    {
        for (int l = 0; l < TILE_NUM; l++)
        {
            if (loop_space[l] != NULL)
            {
                loop_space[l]->loop(dt);
            }
        }
    }
};

struct window
{
    float SCALE_X = 1;
    float SCALE_Y = 1;
    int WIDTH;
    int HEIGHT;
    int keys[200];
    SDL_Window* window;
    SDL_Renderer* renderer;
    SDL_Event event;
};

namespace test {
struct clock clock;
struct window window;
struct renderer renderer;
struct looper looper;
bool running = 1;
int index = 0;
int idblacklist[ENT_NUM + TILE_NUM * NUM_LAYERS];



RGBAcolor tempcolor;


void start(char* name, int w, int h)
{
#include "baseColors.h"
    
    TTF_Init();
    renderer.DGcolor.white();
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

int getID()
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
    SDL_SetRenderDrawColor(window.renderer, renderer.BGcolor.r, renderer.BGcolor.g, renderer.BGcolor.b, renderer.BGcolor.a);
    SDL_RenderClear(window.renderer);
    SDL_SetRenderDrawColor(window.renderer, renderer.DGcolor.r, renderer.DGcolor.g, renderer.DGcolor.b, renderer.DGcolor.a);
    
    if (isDown(SDLK_ESCAPE))
        running = false;
    if (!running)
    {
        SDL_DestroyWindow(window.window);
        SDL_DestroyRenderer(window.renderer);
        TTF_Quit();
        SDL_Quit();
    }
    clock.tick();
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
        std::cout << "WARNING: TEXTURE NOT FOUND\n";
        return IMG_Load(MISSING_TEXTURE_PATH);
    }
    return surface;
}

void draw(float x, float y, SDL_Surface* surf)
{
    SDL_Rect rect;
    rect.x = x;
    rect.y = y;
    rect.w = surf->w * window.SCALE_X;
    rect.h = surf->h * window.SCALE_Y;
    auto tex = SDL_CreateTextureFromSurface(window.renderer, surf);
    SDL_RenderCopy(window.renderer, tex, nullptr, &rect);
    SDL_DestroyTexture(tex);
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

void draw(tile t)
{
    SDL_Rect body;
    body.w = t.getSize().x * window.SCALE_X;
    body.h = t.getSize().y * window.SCALE_Y;
    body.x = t.getPos().x;
    body.y = t.getPos().y;
    
    if (t.isQuad)
    {
        SDL_Rect quad;
        quad.x = t.quad.x;
        quad.y = t.quad.y;
        quad.w = t.quad.w;
        quad.h = t.quad.h;
        auto tex = SDL_CreateTextureFromSurface(window.renderer, t.img);
        SDL_RenderCopyEx(window.renderer, tex, &quad, &body, t.getRotation(), nullptr, SDL_FLIP_NONE);
        SDL_DestroyTexture(tex);
    }
    else
    {
        auto tex = SDL_CreateTextureFromSurface(window.renderer, t.img);
        SDL_RenderCopyEx(window.renderer, tex, nullptr, &body, t.getRotation(), nullptr, SDL_FLIP_NONE);
        SDL_DestroyTexture(tex);
    }
    
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
    renderer.DGcolor.r = c.r;
    renderer.DGcolor.g = c.g;
    renderer.DGcolor.b = c.b;
    renderer.DGcolor.a = c.a;
    
}

void setBGcolor(RGBAcolor c)
{
    renderer.BGcolor.r = c.r;
    renderer.BGcolor.g = c.g;
    renderer.BGcolor.b = c.b;
    renderer.BGcolor.a = c.a;
}

tile* newTile(float x, float y, SDL_Surface* pic, vec4i quad_frame)
{
    tile* t = new tile;
    t->load(x, y, quad_frame.w, quad_frame.h, pic, quad_frame);
    t->id = getID();
    renderer.renderMe(t);
    looper.loopMe(t);
    return t;
}
tile* newTile(float x, float y, SDL_Surface* pic, int xa, int ya, int w, int h)
{
    tile* t = new tile;
    vec4i quad_frame;
    quad_frame.x = xa;
    quad_frame.y = ya;
    quad_frame.w = w;
    quad_frame.h = h;
    t->load(x, y, quad_frame.w, quad_frame.h, pic, quad_frame);
    t->id = getID();
    renderer.renderMe(t);
    looper.loopMe(t);
    return t;
}

tile* newTile(float x, float y, int w, int h, SDL_Surface* pic)
{
    tile* t = new tile;
    t->load(x, y, w, h, pic);
    t->id = getID();
    renderer.renderMe(t);
    looper.loopMe(t);
    return t;
}

tile* newTile(float x, float y, SDL_Surface* pic)
{
    tile* t = new tile;
    int w = pic->w;
    int h = pic->h;
    t->load(x, y, w, h, pic);
    t->id = getID();
    renderer.renderMe(t);
    looper.loopMe(t);
    return t;
}

player* newPlayer(float x, float y, SDL_Surface* pic, vec4i quad_frame)
{
    player* t = new player;
    t->load(x, y, quad_frame.w, quad_frame.h, pic, quad_frame);
    t->id = getID();
    renderer.renderMe(t);
    looper.loopMe(t);
    return t;
}
player* newPlayer(float x, float y, SDL_Surface* pic, int xa, int ya, int w, int h)
{
    player* t = new player;
    vec4i quad_frame;
    quad_frame.x = xa;
    quad_frame.y = ya;
    quad_frame.w = w;
    quad_frame.h = h;
    t->load(x, y, quad_frame.w, quad_frame.h, pic, quad_frame);
    t->id = getID();
    renderer.renderMe(t);
    looper.loopMe(t);
    return t;
}

player* newPlayer(float x, float y, int w, int h, SDL_Surface* pic)
{
    player* t = new player;
    t->load(x, y, w, h, pic);
    t->id = getID();
    renderer.renderMe(t);
    looper.loopMe(t);
    return t;
}

player* newPlayer(float x, float y, SDL_Surface* pic)
{
    player* t = new player;
    int w = pic->w;
    int h = pic->h;
    t->load(x, y, w, h, pic);
    t->id = getID();
    renderer.renderMe(t);
    looper.loopMe(t);
    return t;
}

void newFont(int size)
{
    if (renderer.currentFont == NULL)
        renderer.currentFont = TTF_OpenFont(DEFAULT_FONT, size);
    else
        std::cerr << "DEFAULT FONT ALREADY CREATED" << std::endl;
}

void newFont(char* path, int size)
{
    if (renderer.currentFont == NULL)
        renderer.currentFont = TTF_OpenFont(path, size);
    else
        std::cerr << "DEFAULT FONT ALREADY CREATED" << std::endl;
}

void changeFont(TTF_Font *newFont)
{
    TTF_CloseFont(renderer.currentFont);
    renderer.currentFont = newFont;
}

void changeTextColor(int r, int g, int b, int a)
{
    renderer.TXTCcolor.r = r;
    renderer.TXTCcolor.g = g;
    renderer.TXTCcolor.b = b;
    renderer.TXTCcolor.a = a;
}


void write(float x, float y, char* text)
{
    SDL_Color c;
    c.r = renderer.TXTCcolor.r;
    c.g = renderer.TXTCcolor.g;
    c.b = renderer.TXTCcolor.b;
    c.a = renderer.TXTCcolor.a;
    
    draw(x, y, TTF_RenderText_Solid(renderer.currentFont, text, c));
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
    
    draw(x, y, TTF_RenderText_Shaded(renderer.currentFont, text, c, g));
}



void write(float x, float y, char* text, RGBAcolor dc)
{
    SDL_Color c;
    c.r = dc.r;
    c.g = dc.g;
    c.b = dc.b;
    c.a = dc.a;
    
    draw(x, y, TTF_RenderText_Solid(renderer.currentFont, text, c));
}

void write(float x, float y, RGBAcolor bg, char* text)
{
    SDL_Color c;
    c.r = renderer.TXTCcolor.r;
    c.g = renderer.TXTCcolor.g;
    c.b = renderer.TXTCcolor.b;
    c.a = renderer.TXTCcolor.a;
    
    SDL_Color g;
    g.r = bg.r;
    g.g = bg.g;
    g.b = bg.g;
    g.a = bg.a;
    
    
    draw(x, y, TTF_RenderText_Shaded(renderer.currentFont, text, c, g));
}


}
