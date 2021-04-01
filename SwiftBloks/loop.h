//
//  loop.h
//  SwiftBloks
//
//  Created by Benjamin Emde on 01.04.21.
//

#pragma once

setBGcolor(*blue);

for (int i = 0; i < 6; i++)
{
    for (int j = 0; j < 6; j++)
    {
        drawCube(j, i, 3, 0, isDown(SDLK_0) * 3, test_img);
    }
}

drawCube(4, 3, 0, 0, -1, test_img);
drawCube(5, 3, 0, 0, -1, test_img);
drawCube(4, 5, 0, 0, -1, test_img);
drawCube(5, 0, 0, 0, -1, test_img);
drawCube(6, 0, 0, 0, -1, test_img);
drawCube(6, 0, 0, 0, -2, test_img);
drawCube(7, 0, 0, 0, -1, test_img);
drawCube(7, 0, 0, 0, -2, test_img);
drawCube(7, 0, 0, 0, -3, test_img);
