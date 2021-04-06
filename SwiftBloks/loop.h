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
setScale(5, 5);
auto img = newImage(MISSING_CUBE_TEXTURE_PATH);
setIMGRGB(img, *blue);
setBGcolor(*blue);
ISO::setOffset(400,275);


while(isRunning())
{
    
    
    write(250, 100,ENGINE_NAME_STRING);
}

