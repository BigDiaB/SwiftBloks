//
//  Base_body.h
//  SwiftBloks
//
//  Created by Benjamin Emde on 06.04.21.
//

#pragma once

class body
{
protected:
    vec3f pos;
    vec3f abs_pos;
    vec2f size = {1,1};
public:
    void setPos(float x, float y, float z)
    {
        pos.x = x;
        pos.y = y;
        pos.z = z;
    }
    vec3f getPos()
    {
        return pos;
    }
    void setSize(float sx, float sy)
    {
        size.x = sx;
        size.y = sy;
    }
    vec2f getSize()
    {
        return size;
    }
    void move(int ax, int ay)
    {
        pos.x += ax;
        pos.y += ay;
    }
    virtual void update(float dt) = 0;
    virtual void draw() = 0;
};
