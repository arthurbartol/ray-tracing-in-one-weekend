#pragma once

#include "Utils.h"

class Camera
{
public:
    Camera()
    {
        double aspectRatio = 16.0 / 9.0;
        double viewportHeight = 2.0;
        double viewportWidth = aspectRatio * viewportHeight;
        double focalLength = 1.0;

        origin = Vec3();
        vertical = Vec3(0.0, viewportHeight, 0.0);
        horizontal = Vec3(viewportWidth, 0.0, 0.0);
        lowerLeftCorner = origin - horizontal/2 - vertical/2 - Vec3(0.0, 0.0, focalLength);
    }


    // Methods

    Ray GetRay(double u, double v)
    {
        return Ray(origin, lowerLeftCorner + u*horizontal + v*vertical - origin);
    }

public:
    Vec3 origin;
    Vec3 vertical;
    Vec3 horizontal;
    Vec3 lowerLeftCorner;
};
