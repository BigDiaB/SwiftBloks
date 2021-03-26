//
//  main.cpp
//  SwiftBloks
//
//  Created by Benjamin Emde on 22.03.21.
//
#include "define.h"
#include "engine.hpp"
#include <iostream>
ENGINE e(WINDOW_NAME,WINDOW_WIDTH,WINDOW_HEIGHT);

int main()
{

#include "baseColors.h"
    auto t = e.newTile(200, 200,e.newImage((char*)"assets/test.png"),e.calcQuad(16,1,1));
    e.setScale(8, 8);
    
    while(e.isRunning())
    {
        float  dt = e.getDelta();
        t.loop(dt);
        if (e.isDown(SDLK_a) and not e.isDown(SDLK_d))
            t.move(-100,0);
        elseif (e.isDown(SDLK_d) and not e.isDown(SDLK_a))
            t.move(100,0);
        if (e.isDown(SDLK_w) and not e.isDown(SDLK_s))
            t.move(0,-100);
        elseif (e.isDown(SDLK_s) and not e.isDown(SDLK_w))
            t.move(0,100);
        
    }
    return 0;
}
