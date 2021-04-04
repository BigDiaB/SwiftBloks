//
//  loop.h
//  SwiftBloks
//
//  Created by Benjamin Emde on 01.04.21.
//



#pragma once

RGBAcolor* blue = new RGBAcolor;
blue->black();
blue->setB(120);
setScale(5, 5);
auto img = newImage(MISSING_CUBE_TEXTURE_PATH);
setIMGRGB(img, *blue);
ISO_OFFSET.x = 400;
ISO_OFFSET.y = 275;

setBGcolor(*blue);

for (int i = 0; i < 6; i++)
{
    for (int j = 0; j < 6; j++)
    {
        newCube(j, i, 0);
    }
}

newCube(0, 0, 1);
newCube(1, 0, 1);
newCube(2, 0, 1);
newCube(0, 1, 1);
newCube(0, 2, 1);
newCube(3, 3, 1);


player p;
p.pos.x = 4;
p.pos.y = 4;
p.pos.z = 1;

while(isRunning())
{
    for (int i = 0; i < cube_index; i++)
    {
        if (cubes[i].pos.z == p.pos.z)
            if (cubes[i].pos.x - 1 < p.pos.x or cubes[i].pos.y - 1 < p.pos.y)
                drawCube(&cubes[i]);
    }
    
    
    drawCube(&p);
    
    
    for (int i = 0; i < cube_index; i++)
    {
        if (cubes[i].pos.z == p.pos.z)
            if (cubes[i].pos.x - 1 >= p.pos.x or cubes[i].pos.y - 1 >= p.pos.y)
                drawCube(&cubes[i]);
    }
    p.update(timer.getDelta(), cubes, cube_index);
   
    
//    write(250, 100,ENGINE_NAME_STRING);
}
