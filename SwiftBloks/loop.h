//
//  loop.h
//  SwiftBloks
//
//  Created by Benjamin Emde on 01.04.21.
//

setScale(2, 2);


if (load())
{
    running = false;
    return 2;
}


c.ground();
d.ground();
e.ground();
f.ground();
c.sort();
d.sort();
e.sort();
f.sort();

p.setPos(1,1,1);
p.img.set(MISSING_CUBE_TEXTURE_PATH);

while(isRunning())
{
    float dt = update();
//    c.drawCollider();
//    d.drawCollider();
//    e.drawCollider();
//    f.drawCollider();
    c.draw();
    d.draw();
    e.draw();
    f.draw();
    p.draw();
    p.update(dt);
    
    write(250, 100,ENGINE_NAME_STRING);
    
    if (isDown(keyboard::Escape))
    {
        running = false;
    }
}

return 1;
