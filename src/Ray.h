#pragma once

#include "Vec3.h"

class Ray
{
public:
    Ray() : origin(Vec3()), direction(Vec3()) {}
    Ray(Vec3 origin, Vec3 direction) : origin(origin), direction(direction) {}


    // Methods

    Vec3 At(double t) const
    {
        return origin + (t * direction);
    }

public:
    Vec3 origin;
    Vec3 direction;
};
