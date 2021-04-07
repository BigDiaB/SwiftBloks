//
//  load.h
//  SwiftBloks
//
//  Created by Benjamin Emde on 01.04.21.
//

int load()
{
    ISO::setOffset(575,100);
    
    return 1;
}

float update()
{
    float dt = timer.getDelta();
    return dt;
}

ISO::CHUNK c{0,0,0};
ISO::CHUNK d{0,1,0};
ISO::CHUNK e{1,0,0};
ISO::CHUNK f{1,1,0};
ISO::CUBE  p;
