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
    vec2f vel;
    float speed = 1;
    vec3f pos = {0,0,0};
    vec2f size;
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
        vel.x += ax;
        vel.y += ay;
    }
    virtual void update(float dt)
    {
        pos.x += (vel.x * dt) * speed;
        pos.y += (vel.y * dt) * speed;
        vel.x *= pow(0.002, dt);
        vel.y *= pow(0.002, dt);
    }
};
