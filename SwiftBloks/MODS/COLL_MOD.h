//
//  COLL_MOD.h
//  SwiftBloks
//
//  Created by Benjamin Emde on 05.04.21.
//

#pragma once
namespace COLL
{
    bool AABB(float x1, float y1, float w1, float h1, float x2, float y2, float w2, float h2)
    {
        return
        x1 < x2+w2 and
        x2 < x1+w1 and
        y1 < y2+h2 and
        y2 < y1+h1;
    }

    vec2i getDirection(vec3f pos1, float w1, float h1, vec3f pos2)
    {
        vec2i result;
        result.x = 0;
        result.y = 0;
        
        if (pos1.x + w1 <= pos2.x)
            result.x = 1;
        if (pos1.x + w1 >= pos2.x)
            result.x = -1;
        
        if (pos1.y + h1 <= pos2.y)
            result.y = 1;
        if (pos1.y + h1 >= pos2.y)
            result.y = -1;
        return result;
    }
};
