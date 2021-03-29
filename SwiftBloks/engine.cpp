//
//  engine.cpp
//  SwiftBloks
//
//  Created by Benjamin Emde on 23.03.21.
//

#include "define.h" // engine.hpp already included in define.h
//#include "engine.hpp"
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
    
    TTF_Init();
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
        TTF_Quit();
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
    
    if (t.isQuad)
    {
    quad.x = t.quad.x;
    quad.y = t.quad.y;
    quad.w = t.quad.w;
    quad.h = t.quad.h;
    auto tex = SDL_CreateTextureFromSurface(renderer, t.img);
    SDL_RenderCopyEx(renderer, tex, &quad, &body, t.getRotation(), nullptr, SDL_FLIP_NONE);
    SDL_DestroyTexture(tex);
    }
    else
    {
        auto tex = SDL_CreateTextureFromSurface(renderer, t.img);
        SDL_RenderCopyEx(renderer, tex, nullptr, &body, t.getRotation(), nullptr, SDL_FLIP_NONE);
        SDL_DestroyTexture(tex);
    }
    
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

tile* ENGINE::newTile(float x, float y, SDL_Surface* pic, vec4i quad_frame)
{
    tile* t = new tile;
    t->load(x, y, quad_frame.w, quad_frame.h, pic, quad_frame);
    t->id = getID();
    Renderer.renderMe(t);
    Looper.loopMe(t);
    return t;
}
tile* ENGINE::newTile(float x, float y, SDL_Surface* pic, int xa, int ya, int w, int h)
{
    tile* t = new tile;
    vec4i quad_frame;
    quad_frame.x = xa;
    quad_frame.y = ya;
    quad_frame.w = w;
    quad_frame.h = h;
    t->load(x, y, quad_frame.w, quad_frame.h, pic, quad_frame);
    t->id = getID();
    Renderer.renderMe(t);
    Looper.loopMe(t);
    return t;
}

tile* ENGINE::newTile(float x, float y, int w, int h, SDL_Surface* pic)
{
    tile* t = new tile;
    t->load(x, y, w, h, pic);
    t->id = getID();
    Renderer.renderMe(t);
    Looper.loopMe(t);
    return t;
}

tile* ENGINE::newTile(float x, float y, SDL_Surface* pic)
{
    tile* t = new tile;
    int w = pic->w;
    int h = pic->h;
    t->load(x, y, w, h, pic);
    t->id = getID();
    Renderer.renderMe(t);
    Looper.loopMe(t);
    return t;
}

player* ENGINE::newPlayer(float x, float y, SDL_Surface* pic, vec4i quad_frame)
{
    player* t = new player;
    t->load(x, y, quad_frame.w, quad_frame.h, pic, quad_frame);
    t->id = getID();
    Renderer.renderMe(t);
    Looper.loopMe(t);
    return t;
}
player* ENGINE::newPlayer(float x, float y, SDL_Surface* pic, int xa, int ya, int w, int h)
{
    player* t = new player;
    vec4i quad_frame;
    quad_frame.x = xa;
    quad_frame.y = ya;
    quad_frame.w = w;
    quad_frame.h = h;
    t->load(x, y, quad_frame.w, quad_frame.h, pic, quad_frame);
    t->id = getID();
    Renderer.renderMe(t);
    Looper.loopMe(t);
    return t;
}

player* ENGINE::newPlayer(float x, float y, int w, int h, SDL_Surface* pic)
{
    player* t = new player;
    t->load(x, y, w, h, pic);
    t->id = getID();
    Renderer.renderMe(t);
    Looper.loopMe(t);
    return t;
}

player* ENGINE::newPlayer(float x, float y, SDL_Surface* pic)
{
    player* t = new player;
    int w = pic->w;
    int h = pic->h;
    t->load(x, y, w, h, pic);
    t->id = getID();
    Renderer.renderMe(t);
    Looper.loopMe(t);
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

void renderer::renderMe(tile* t)
{
    for (int i = 0; i < TILE_NUM; i++)
    {
    if (things[t->layer].tiles[i] == NULL)
    {
        things[t->layer].tiles[i] = t;
        break;
    }
    }
}

void renderer::destroyMe(tile* t)
{
    for (int i = 0; i < TILE_NUM; i++)
    {
        if (t->id == things[t->layer].tiles[i]->id)
            things[t->layer].tiles[i] = NULL;
    }
}

void renderer::renderMe(player* t)
{
    for (int i = 0; i < TILE_NUM; i++)
    {
    if (things[t->layer].tiles[i] == NULL)
    {
        things[t->layer].tiles[i] = t;
        break;
    }
    }
}

void renderer::destroyMe(player* t)
{
    for (int i = 0; i < TILE_NUM; i++)
    {
        if (t->id == things[t->layer].tiles[i]->id)
            things[t->layer].tiles[i] = NULL;
    }
}

void renderer::render()
{
    for (int l = 0; l < NUM_LAYERS; l++)
    {
        for (int g = 0; g < TILE_NUM; g++)
        {
            if (things[l].tiles[g] != NULL)
            {
                things[l].tiles[g]->render();
            }
        }
    }
}


void looper::loopMe(tile* t)
{
    for (int i = 0; i < TILE_NUM; i++)
    {
    if (things[i] == NULL)
    {
        things[i] = t;
        break;
    }
    }
}

void looper::stopme(tile* t)
{
    for (int i = 0; i < TILE_NUM; i++)
    {
        if (t->id == things[i]->id)
            things[i] = NULL;
    }
}

void looper::loopMe(player* t)
{
    for (int i = 0; i < TILE_NUM; i++)
    {
    if (things[i] == NULL)
    {
        things[i] = t;
        break;
    }
    }
}

void looper::stopMe(player* t)
{
    for (int i = 0; i < TILE_NUM; i++)
    {
        if (t->id == things[i]->id)
            things[i] = NULL;
    }
}

void looper::loop()
{
    for (int l = 0; l < TILE_NUM; l++)
    {
        if (things[l] != NULL)
        {
            things[l]->loop(e.getDelta());
        }
    }
}

void texter::newFont(int size)
{
    if (currentFont == NULL)
        currentFont = TTF_OpenFont(DEFAULT_FONT, size);
    else
        std::cerr << "DEFAULT FONT ALREADY CREATED" << std::endl;
}

void texter::newFont(char* path, int size)
{
    if (currentFont == NULL)
        currentFont = TTF_OpenFont(path, size);
    else
        std::cerr << "DEFAULT FONT ALREADY CREATED" << std::endl;
}

void texter::changeFont(TTF_Font *newFont)
{
    TTF_CloseFont(currentFont);
    currentFont = newFont;
}

void texter::changeColor(int r, int g, int b, int a)
{
    currentColor.r = r;
    currentColor.g = g;
    currentColor.b = b;
    currentColor.a = a;
}


void texter::write(float x, float y, char* text)
{
    SDL_Color c;
    c.r = currentColor.r;
    c.g = currentColor.g;
    c.b = currentColor.b;
    c.a = currentColor.a;
    
    e.draw(x, y, TTF_RenderText_Solid(currentFont, text, c));
}
void texter::write(float x, float y, RGBAcolor bg, char* text, RGBAcolor dc)
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
    
    e.draw(x, y, TTF_RenderText_Shaded(currentFont, text, c, g));
}



void texter::write(float x, float y, char* text, RGBAcolor dc)
{
    SDL_Color c;
    c.r = dc.r;
    c.g = dc.g;
    c.b = dc.b;
    c.a = dc.a;
    
    e.draw(x, y, TTF_RenderText_Solid(currentFont, text, c));
}

void texter::write(float x, float y, RGBAcolor bg, char* text)
{
    SDL_Color c;
    c.r = currentColor.r;
    c.g = currentColor.g;
    c.b = currentColor.b;
    c.a = currentColor.a;
    
    SDL_Color g;
    g.r = bg.r;
    g.g = bg.g;
    g.b = bg.g;
    g.a = bg.a;

    
    e.draw(x, y, TTF_RenderText_Shaded(currentFont, text, c, g));
}
