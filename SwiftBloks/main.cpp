//
//  main.cpp
//  SwiftBloks
//
//  Created by Benjamin Emde on 22.03.21.
//
#define elseif else if
#include "engine.hpp"
#include <iostream>
ENGINE e(1080,720);
int main()
{
#include "baseColors.h"
    auto t = e.newTile(200, 200, e.newImage((char*)"assets/test.png"));
    e.setScale(8, 8);
    
    while(e.isRunning())
    {
        e.test();
        
        if (e.isDown(SDLK_a) and not e.isDown(SDLK_d))
        {
            t.move(-1, 0);
        }
        elseif (e.isDown(SDLK_d) and not e.isDown(SDLK_a))
        {
            t.move(1, 0);
        }
        
        if (e.isDown(SDLK_w) and not e.isDown(SDLK_s))
        {
            t.move(0, -1);
        }
        elseif (e.isDown(SDLK_s) and not e.isDown(SDLK_w))
        {
            t.move(0, 1);
        }

            
    }
    return 0;
}
