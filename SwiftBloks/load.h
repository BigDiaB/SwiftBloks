//
//  load.h
//  SwiftBloks
//
//  Created by Benjamin Emde on 01.04.21.
//

void drawCube(int x, int y, SDL_Surface* tex)
{
    draw(150 + x * (10 * window.SCALE_X )- y * (10 * window.SCALE_X), 100 + x * (5 * window.SCALE_Y) + y * (5 * window.SCALE_Y), tex);
}

void drawCube(int x, int y, int xmod, int ymod, int zmod, SDL_Surface* tex)
{
    draw(150 + (x + xmod) * (10 * window.SCALE_X )- (y + ymod) * (10 * window.SCALE_X),
         100 + (x + xmod) * (5 * window.SCALE_Y) + (y + ymod) * (5 * window.SCALE_Y) + zmod * window.SCALE_Y * 12,
         tex);
}
