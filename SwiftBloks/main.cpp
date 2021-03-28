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

//#include "baseColors.h"
   e.newPlayer(200, 200,e.newImage((char*)"assets/test.png"));
//    auto g = e.newTile(200, 200, e.newImage((char*)"assets/test.png"));
    e.setScale(2, 2);
    
    for (int i = 0; i < 9; i++)
    {
        for (int j = 0; j < 15; j++)
        {
            e.newTile((1+j) * 64, (1+i) * 64, e.newImage((char*)"assets/ground_grass_1.png"));
        }
    }
    
        while(e.isRunning())
    {
//        float  dt = e.getDelta();
        e.Renderer.render();
        e.Looper.loop(e.getDelta());
//        t.loop(dt);
        
    }
    return 0;
}


float Q_rsqrt(float number)
{
    long i;
    float x2, y;
    const float threehalfs = 1.5f;
    
    x2 = number * 0.5f;
    y = number;
    i = * ( long * ) &y;
    i = 0x5f3759df - ( i >> 1 );
    y = * ( float * ) &i;
    y = y * ( threehalfs - ( x2 * y * y ) );
//    y = y * ( threehalfs - ( x2 * y * y ) );
    
    return y;
}
