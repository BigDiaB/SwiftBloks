//
//  main.cpp
//  SwiftBloks
//
//  Created by Benjamin Emde on 22.03.21.
//
#include "namespace.h"
#include "define.h"
//#include <iostream>

int main()
{
    test::start(WINDOW_NAME, WINDOW_WIDTH, WINDOW_HEIGHT);
    #include "baseColors.h"
    test::setScale(10, 10);
    test::tempcolor.setB(255);
    test::setBGcolor(test::tempcolor);
    auto p = test::newPlayer(100, 100, test::newImage((char*)"there is no png here"), test::calcQuad(32, 32, 1, 1));
    while(test::isRunning())
    {
//        test::draw(200, 200, test::newImage("Hier gibt es kein Bild für dich"));
        test::draw(*p);
        test::looper.loop(test::clock.getDelta());
            if (test::isDown(SDLK_r))
                p->rotate(false, test::clock.getDelta() * 200);
            if (test::isDown(SDLK_a) and not test::isDown(SDLK_d))
                p-> move(-100,0);
            elseif (test::isDown(SDLK_d) and not test::isDown(SDLK_a))
                p->move(100,0);
            if (test::isDown(SDLK_w) and not test::isDown(SDLK_s))
                p->move(0,-100);
            elseif (test::isDown(SDLK_s) and not test::isDown(SDLK_w))
                p->move(0,100);
    }
    return 0;
}
