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
    auto t = e.newPlayer(200, 200,e.newImage((char*)"assets/test.png"),e.calcQuad(32,1,1));
//    auto g = e.newTile(200, 200, e.newImage((char*)"assets/test.png"));
    e.setScale(8, 8);
    
    while(e.isRunning())
    {
        float  dt = e.getDelta();
        t.loop(dt);
        
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
