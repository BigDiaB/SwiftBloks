//
//  util.h
//  SwiftBloks
//
//  Created by Benjamin Emde on 25.03.21.
//

#ifndef util_h
#define util_h

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
    float x = 1;
    float y = 1;
};

struct vec2i
{
    int x = 1;
    int y = 1;
};

struct vec4i
{
    int x = 1;
    int y = 1;
    int w = 1;
    int h = 1;
};

struct physics
{
    float friction = 300;
    float weight = 0;
};

#endif /* util_h */
