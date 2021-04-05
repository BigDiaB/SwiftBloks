//
//  loop.h
//  SwiftBloks
//
//  Created by Benjamin Emde on 01.04.21.
//

#pragma once

RGBAcolor* blue = new RGBAcolor;
blue->black();
blue->setB(120);
setScale(2, 2);
ISO::setOffset(450, 175);

setBGcolor(*blue);
cube c;
while(isRunning())
{
    float dt = timer.getDelta();
    c.movement(dt);
    ISO::drawCube(c.getPos().x, c.getPos().y, c.getPos().z);
//    write(250, 100,ENGINE_NAME_STRING);
}
