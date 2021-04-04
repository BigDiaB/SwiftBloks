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
    start(WINDOW_NAME, WINDOW_WIDTH, WINDOW_HEIGHT);
    #include LOOP_FILE
    return 0;
}
