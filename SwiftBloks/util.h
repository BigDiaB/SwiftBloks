//
//  util.h
//  SwiftBloks
//
//  Created by Benjamin Emde on 25.03.21.
//

#ifndef util_h
#define util_h
#include <SDL2/SDL.h>


struct RGBAcolor
{
    float r = 1;
    float g = 1;
    float b = 1;
    float a = 255;
    
    void black()
    { r = 0; g = 0; b = 0;}
    void white()
    { r = 255; g = 255; b = 255;}
    
    void setR(float newR)
    { r = newR;}
    void setG(float newG)
    { g = newG;}
    void setB(float newB)
    { b = newB;}
    void setA(float newA)
    { a = newA;}
};

struct vec2f
{
    float x,y;
};

struct vec2i
{
    int x,y;
};

struct vec3f
{
    float x,y,z;
};

struct vec3i
{
    int x,y,z;
};

struct vec4i
{
    int x,y,w,h;
};

namespace keyboard
{
    int Escape = SDLK_ESCAPE;
    int Return = SDLK_RETURN;
    int A = SDLK_a;
    int B = SDLK_b;
    int C = SDLK_c;
    int D = SDLK_d;
    int E = SDLK_e;
    int F = SDLK_f;
    int G = SDLK_g;
    int H = SDLK_h;
    int I = SDLK_i;
    int J = SDLK_j;
    int K = SDLK_k;
    int L = SDLK_l;
    int M = SDLK_m;
    int N = SDLK_n;
    int O = SDLK_o;
    int P = SDLK_p;
    int Q = SDLK_q;
    int R = SDLK_r;
    int S = SDLK_s;
    int T = SDLK_t;
    int U = SDLK_u;
    int V = SDLK_v;
    int W = SDLK_w;
    int X = SDLK_x;
    int Y = SDLK_y;
    int Z = SDLK_z;
    int NUM_0 = SDLK_0;
    int NUM_1 = SDLK_1;
    int NUM_2 = SDLK_2;
    int NUM_3 = SDLK_3;
    int NUM_4 = SDLK_4;
    int NUM_5 = SDLK_5;
    int NUM_6 = SDLK_6;
    int NUM_7 = SDLK_7;
    int NUM_8 = SDLK_8;
    int NUM_9 = SDLK_9;
};
#endif /* util_h */
