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

class CUBE: public body
{
public:
    void update(float dt) override
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
    
//    void collide(CHUNK chunk, int cube_index)
//    {
//        for (int i = 0; i < chunk.getSize().x; i++)
//        {
//            if (COLL::AABB(getPos().x,getPos().y,1,1,getPos().z, chunk.bloks[i].getPos().x,chunk.bloks[i].getPos().y,1,1,chunk.bloks[i].getPos().z))
//            {
//                drawCubeCollider(chunk.bloks[i].getPos().x, chunk.bloks[i].getPos().y, chunk.bloks[i].getPos().z);
//                vec2i dir = COLL::getDirection(pos, 0.4, 0.4, chunk.bloks[i].getPos());
//
//                if (dir.x < 0 and vel.x < 0)
//                {
//                    vel.x *= -COLLISION_RESPONSE_FACTOR;
//                }
//                elseif (dir.x > 0 and vel.x > 0)
//                {
//                    vel.x *= -COLLISION_RESPONSE_FACTOR;
//                }
//
//                if (dir.y < 0 and vel.y < 0)
//                {
//                    vel.y *= -COLLISION_RESPONSE_FACTOR;
//                }
//                elseif (dir.y > 0 and vel.y > 0)
//                {
//                    vel.y *= -COLLISION_RESPONSE_FACTOR;
//                }
//
//            }
//        }
//    }
    
    void draw() override
    {
        drawCube(pos.x, pos.y, pos.z);
    }
};

class CHUNK
{
public:
    vec3i pos;
    int fill = 0;
    int sorted = 0;
    int size = 10 * 10 * 5;
    int dimensions[3] = {10,10,5};
    CUBE bloks[10 * 10 * 5];
    CUBE bloks_sorted[10 * 10 * 5];
    
    void add(int x, int y, int z)
    {
        CUBE temp;
        temp.setPos(x, y, z);
        bloks[fill] = temp;
        fill++;
    }
    
    void sort()
    {
        for (int z = 0; z < dimensions[2]; z++)
        {
            for (int y = 0; y < dimensions[1]; y++)
            {
                for (int x = 0; x < dimensions[0]; x++)
                {
                    for (int i = 0; i < size; i++)
                    {
                        if (&bloks[i] != NULL)
                        {
                            if (bloks[i].getPos().x == x and bloks[i].getPos().y == y and bloks[i].getPos().z == z)
                            {
                                bloks_sorted[sorted] = bloks[i];
                                sorted++;
                            }
                        }
                    }
                }
            }
        }
    }
    
    void ground()
    {
        for (int y = 0; y < dimensions[1]; y++)
        {
            for (int x = 0; x < dimensions[0]; x++)
            {
                add(x, y, 0);
            }
        }
    }
    
    void draw()
    {
        for (int i = 0; i < size; i++)
        {
            if (&bloks_sorted[i] != NULL)
            {
                drawCube(bloks_sorted[i].getPos().x + pos.x * dimensions[0], bloks_sorted[i].getPos().y + pos.y * dimensions[1], bloks_sorted[i].getPos().z + pos.z * dimensions[2]);
            }
        }
    }
};






};

