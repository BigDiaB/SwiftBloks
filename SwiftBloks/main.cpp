//
//  main.cpp
//  SwiftBloks
//
//  Created by Benjamin Emde on 22.03.21.
//
#include "define.h"
#include ENGINE_PATH
using namespace ENGINE_NAME;

#include LOAD_FILE

int main()
{
    RGBAcolor* blue = new RGBAcolor;
    blue->black();
    blue->setB(120);
    start(WINDOW_NAME, WINDOW_WIDTH, WINDOW_HEIGHT);
    while(isRunning())
    {
        #include LOOP_FILE
    }
    return 0;
}
