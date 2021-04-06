//
//  main.cpp
//  SwiftBloks
//
//  Created by Benjamin Emde on 22.03.21.
//

#define elseif else if
#define nullstr (char*)"This is a nullstring. It is just a string, that should resemble a path, which doesn't actually lead anywhere"
#define WINDOW_NAME (char*)"SwiftBloks"
#define WINDOW_WIDTH 1080
#define WINDOW_HEIGHT 720
#define ID_NUM 100
#define DEFAULT_FONT "assets/font.ttf"
#define MISSING_TEXTURE_PATH "assets/NOT_FOUND.png"
#define MISSING_CUBE_TEXTURE_PATH (char*)"assets/NOT_FOUND_ISO_CUBE.png"
#define ENGINE_NAME SwiftBloks
#define ENGINE_NAME_STRING (char*)"SwiftBloks"
#define LOOP_FILE "loop.h"
#define LOAD_FILE "load.h"
#define ENGINE_PATH "SwiftBloks.h"
#define ENGINE_MOD_PATH "SwiftMods.h"
#define ENGINE_MOD_INIT using namespace ENGINE_NAME;

#include ENGINE_PATH
using namespace ENGINE_NAME;
#include ENGINE_MOD_PATH
#include LOAD_FILE

int main()
{
    start(WINDOW_NAME, WINDOW_WIDTH, WINDOW_HEIGHT);
    #include LOOP_FILE
    return 0;
}
