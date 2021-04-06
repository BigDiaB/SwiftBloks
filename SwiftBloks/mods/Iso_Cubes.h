//
//  Iso_Cubes.h
//  SwiftBloks
//
//  Created by Benjamin Emde on 06.04.21.
//

#pragma once
ENGINE_MOD_INIT
#define CUBE_HALF_SURFACE_HEIGHT 10 * window.SCALE_X
#define CUBE_HALF_SURFACE_WIDTH 5 * window.SCALE_Y
#define Z_AXIS_VALUE 12  * window.SCALE_Y
#define CHUNK_SIZE 16
#define CHUNK_HEIGHT_LIMIT 2
#define COLLISION_RESPONSE_FACTOR 0.7
#define LAYERING_DISTANCE_X 0.95
#define LAYERING_DISTANCE_Y 0.95

namespace ISO
{
vec2i OFFSET;
auto IMG = newImage(nullstr);
void setOffset(int x, int y)
{
    OFFSET.x = x;
    OFFSET.y = y;
}

void drawCube(float x, float y, float z, SDL_Surface* tex)
{
    draw(OFFSET.x  + x * CUBE_HALF_SURFACE_HEIGHT - y * CUBE_HALF_SURFACE_HEIGHT, OFFSET.y + x * CUBE_HALF_SURFACE_WIDTH + y * CUBE_HALF_SURFACE_WIDTH - z * Z_AXIS_VALUE, tex);
}

void drawCube(float x, float y, float z)
{
    draw(OFFSET.x  + x * CUBE_HALF_SURFACE_HEIGHT - y * CUBE_HALF_SURFACE_HEIGHT, OFFSET.y + x * CUBE_HALF_SURFACE_WIDTH + y * CUBE_HALF_SURFACE_WIDTH - z * Z_AXIS_VALUE, IMG);
}

void drawCubeCollider(float x, float y, float z)
{
    rect(false,OFFSET.x  + x * CUBE_HALF_SURFACE_HEIGHT - y * CUBE_HALF_SURFACE_HEIGHT, OFFSET.y + x * CUBE_HALF_SURFACE_WIDTH + y * CUBE_HALF_SURFACE_WIDTH - z * Z_AXIS_VALUE, 20,26);
}


class cube: public body
{
public:
    void movement(float dt)
    {
        pos.x += (vel.x * dt) * speed;
        pos.y += (vel.y * dt) * speed;
        vel.x *= pow(0.002, dt);
        vel.y *= pow(0.002, dt);
        if (isDown(SDLK_w) and not isDown(SDLK_s))
        {
            vel.y += -speed;
        }
        elseif (isDown(SDLK_s) and not isDown(SDLK_w))
        {
            vel.y += speed;
        }
        if (isDown(SDLK_a) and not isDown(SDLK_d))
        {
            vel.x += -speed;
        }
        elseif (isDown(SDLK_d) and not isDown(SDLK_a))
        {
            vel.x += speed;
        }
    }
    
    void collide(body cubes[], int cube_index)
    {
        for (int i = 0; i < CHUNK_SIZE; i++)
        {
            for (int j = 0; i < CHUNK_SIZE; j++)
            if (COLL::AABB(getPos().x,getPos().y,1,1,getPos().z, cubes[i].getPos().x,cubes[i].getPos().y,1,1,cubes[i].getPos().z))
            {
                drawCubeCollider(cubes[i].getPos().x, cubes[i].getPos().y, cubes[i].getPos().z);
                vec2i dir = COLL::getDirection(pos, 0.4, 0.4, cubes[i].getPos());
                
                if (dir.x < 0 and vel.x < 0)
                {
                    vel.x *= -COLLISION_RESPONSE_FACTOR;
                }
                elseif (dir.x > 0 and vel.x > 0)
                {
                    vel.x *= -COLLISION_RESPONSE_FACTOR;
                }
                
                if (dir.y < 0 and vel.y < 0)
                {
                    vel.y *= -COLLISION_RESPONSE_FACTOR;
                }
                elseif (dir.y > 0 and vel.y > 0)
                {
                    vel.y *= -COLLISION_RESPONSE_FACTOR;
                }
                
            }
        }
    }
    
};


class ISO_CHUNK
{
    int size = 10 * 10 * 5;
    body bloks[10 * 10 * 5];
};

};

