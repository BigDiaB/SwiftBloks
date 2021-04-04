//
//  load.h
//  SwiftBloks
//
//  Created by Benjamin Emde on 01.04.21.
//
struct vec3f
{
    float x,y,z;
};
auto IMG = newImage(MISSING_CUBE_TEXTURE_PATH);
#define CUBE_HALF_SURFACE_HEIGHT 10 * window.SCALE_X
#define CUBE_HALF_SURFACE_WIDTH 5 * window.SCALE_Y
#define Z_AXIS_VALUE 12  * window.SCALE_Y
vec2i ISO_OFFSET;

void drawCube(float x, float y, float z, SDL_Surface* tex)
{
    draw(ISO_OFFSET.x  + x * CUBE_HALF_SURFACE_HEIGHT - y * CUBE_HALF_SURFACE_HEIGHT, ISO_OFFSET.y + x * CUBE_HALF_SURFACE_WIDTH + y * CUBE_HALF_SURFACE_WIDTH - z * Z_AXIS_VALUE, tex);
}

void drawCube(float x, float y, float z)
{
    draw(ISO_OFFSET.x  + x * CUBE_HALF_SURFACE_HEIGHT - y * CUBE_HALF_SURFACE_HEIGHT, ISO_OFFSET.y + x * CUBE_HALF_SURFACE_WIDTH + y * CUBE_HALF_SURFACE_WIDTH - z * Z_AXIS_VALUE, IMG);
}

void drawCubeCollider(float x, float y, float z)
{
    rect(false,ISO_OFFSET.x  + x * CUBE_HALF_SURFACE_HEIGHT - y * CUBE_HALF_SURFACE_HEIGHT, ISO_OFFSET.y + x * CUBE_HALF_SURFACE_WIDTH + y * CUBE_HALF_SURFACE_WIDTH - z * Z_AXIS_VALUE, 20,26);
}

class cube
{
public:
    vec3f pos;
    vec2i size;
    SDL_Surface* img;
};

bool AABB(float x1, float y1, int w1, int h1, int l1, float x2, float y2, int w2, int h2, int l2)
{
    return
    x1 < x2+w2 and
    x2 < x1+w1 and
    y1 < y2+h2 and
    y2 < y1+h1 and
    l1 == l2;
}


bool AABB(cube c1, cube c2)
{
    return AABB(c1.pos.x, c1.pos.y, 1, 1, c1.pos.z, c2.pos.x, c2.pos.y, 1, 1, c2.pos.z);
}

vec2i getDirection(vec3f pos1, float w1, float h1, vec3f pos2)
{
    vec2i result;
    result.x = 0;
    result.y = 0;
    
    if (pos1.x + w1 <= pos2.x)
        result.x = 1;
    if (pos1.x + w1 >= pos2.x)
        result.x = -1;
    
    if (pos1.y + h1 <= pos2.y)
        result.y = 1;
    if (pos1.y + h1 >= pos2.y)
        result.y = -1;
    return result;
}




class player : public cube
{
public:
    vec2f vel;
    float speed = 0.1;
    SDL_Surface* img;
    
    void update(float dt, cube cubes[], int cube_index)
    {
        move(dt);
        collide(cubes, cube_index);
    }
    
    void move(float dt)
    {
        pos.x += vel.x * dt;
        pos.y += vel.y * dt;
        vel.x *= pow(0.002, timer.getDelta());
        vel.y *= pow(0.002, timer.getDelta());
        if (vel.x < 0.01 && vel.x > 0)
            vel.x = 0;
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
    
    void collide(cube cubes[], int cube_index)
    {
        for (int i = 0; i < cube_index; i++)
        {
            if (AABB(*this, cubes[i]))
            {
                drawCubeCollider(cubes[i].pos.x, cubes[i].pos.y, cubes[i].pos.z);
                vec2i dir = getDirection(pos, 0.4, 0.4, cubes[i].pos);
                
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

cube cubes[100];
int cube_index = 0;
void newCube(float x, float y, float z)
{
    cube* c = new cube;
    c->pos.x = x;
    c->pos.y = y;
    c->pos.z = z;
    cubes[cube_index] = *c;
    cube_index++;
}

void draw_cubes()
{
    for (int i = 0; i < cube_index; i++)
    {
        drawCube(cubes[i].pos.x, cubes[i].pos.y, cubes[i].pos.z);
    }
}

void drawCube(cube* c)
{
    drawCube(c->pos.x, c->pos.y, c->pos.z);
}
