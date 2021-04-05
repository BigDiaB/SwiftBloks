//
//  THINGS_MOD.h
//  SwiftBloks
//
//  Created by Benjamin Emde on 05.04.21.
//

#pragma once

class body
{
protected:
    vec2f vel;
    float speed = 0.1;
    vec3f pos;
    vec2f size;
public:
    vec3f getPos()
    {
        return pos;
    }
    vec2f getSize()
    {
        return size;
    }
    void move(int ax, int ay)
    {
        vel.x += ax;
        vel.y += ay;
    }
};
