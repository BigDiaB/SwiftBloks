//
//  main.cpp
//  SwiftBloks
//
//  Created by Benjamin Emde on 22.03.21.
//
#include "define.h"
#include ENGINE_PATH
using namespace ENGINE_NAME;

int main()
{
    RGBAcolor* black = new RGBAcolor;
    black->black();

    RGBAcolor* white = new RGBAcolor;
    white->white();

    RGBAcolor* red = new RGBAcolor;
    red->black();
    red->setR(255);

    RGBAcolor* blue = new RGBAcolor;
    blue->black();
    blue->setB(255);

    RGBAcolor* green = new RGBAcolor;
    green->black();
    green->setG(255);
    
    start(WINDOW_NAME, WINDOW_WIDTH, WINDOW_HEIGHT);
    setScale(10, 10);
    tempcolor.setB(255);
    setBGcolor(*blue);
    auto tex = newImage((char*)"No pic for u");
    while(isRunning())
    {
        draw(100, 100, tex);
    }
    return 0;
}
