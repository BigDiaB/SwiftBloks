//
//  engine.hpp
//  SwiftBloks
//
//  Created by Benjamin Emde on 23.03.21.
//

#ifndef engine_hpp
#define engine_hpp



#include "util.h"
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_ttf.h>
#include "objects.hpp"

class ENGINE
{
    float SCALE_X = 1;
    float SCALE_Y = 1;
    int WIDTH;
    int HEIGHT;
    int keys[200];
    RGBAcolor DGcolor;
    RGBAcolor BGcolor;
    SDL_Window* window;
    SDL_Renderer* renderer;
    SDL_Event event;
    bool running = 1;
    int index = 0;
    int idblacklist[ENT_NUM + TILE_NUM];
    tile* tiles[TILE_NUM];
    unsigned int last_tick_time = 0;
    float dt = 0;
    void tick();
public:
    float getDelta();
    ENGINE(char* name, int w, int h);
    void loop();
    bool isRunning();
    bool isDown(int key);
    SDL_Surface* newImage(char* path);
    
    void draw(float x, float y, SDL_Surface* surf);
    void draw(float x, float y, SDL_Surface* surf, float sx, float sy);
    void draw(tile t);
    void draw(float x, float y, SDL_Surface* surf, int xa, int ya, int w, int h, float sx, float sy);
    
    void rect(bool fill, float x, float y, int w, int h);
    void rect(bool fill, float x, float y, int w, int h, float sx, float sy);
    
    void setScale(float newX, float newY);
    void setIMGRGB(SDL_Surface* surf, RGBAcolor c);
    void setIMGALPHA(SDL_Surface* surf, int alpha);
    void setColor(RGBAcolor c);
    void setBGcolor(RGBAcolor c);
    
    int getID();
    vec4i calcQuad(int w, int h, int xid, int yid);
    vec4i calcQuad(int h, int xid, int yid);
    tile newTile(float x, float y, SDL_Surface* pic, vec4i quad_frame);
    tile newTile(float x, float y, SDL_Surface* pic, int xa, int ya, int w, int h);
    tile newTile(float x, float y, int w, int h, SDL_Surface* pic);
    tile newTile(float x, float y, SDL_Surface* pic);
    
    player newPlayer(float x, float y, SDL_Surface* pic, vec4i quad_frame);
    player newPlayer(float x, float y, SDL_Surface* pic, int xa, int ya, int w, int h);
    player newPlayer(float x, float y, int w, int h, SDL_Surface* pic);
    player newPlayer(float x, float y, SDL_Surface* pic);
    
    
    
    RGBAcolor color;
    void debug(tile t);
};
#endif /* engine_hpp */
