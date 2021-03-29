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
    e.newPlayer(200, 200,e.newImage((char*)"assets/test.png"));
    e.setScale(2, 2);
    
    for (int i = 0; i < 9; i++)
    {
        for (int j = 0; j < 15; j++)
        {
            e.newTile((1+j) * 64, (1+i) * 64, e.newImage((char*)"assets/ground_grass_1.png"));
        }
    }
    
    e.Text.newFont(40);
    e.Text.changeColor(255, 255, 255, 255);
    
        while(e.isRunning())
    {
        e.Renderer.render();
        e.Looper.loop();
        e.Text.write(300, 300, (char*)"SwiftBloks", red);
        
    }
    return 0;
}
