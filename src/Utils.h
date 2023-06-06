#pragma once

#include <cmath>
#include <memory>
#include <limits>
#include <cstdlib>


// Usings

using std::sqrt;
using std::shared_ptr;
using std::make_shared;


// Constants

const double _INFINITY = std::numeric_limits<double>::infinity();
const double PI = 3.1415926535897932385;


// Utility Functions

inline double Degrees2Radians(double degrees)
{
    return degrees * PI / 180.0;
}

inline double RandomDouble()
{
    // Returns a random real in [0,1]
    return rand() / (RAND_MAX + 1.0);
}

inline double RandomDouble(double min, double max)
{
    // Returns a random real in [min, max]
    return min + (max - min) * RandomDouble();
}

inline double Clamp(double x, double min, double max)
{
    if (x < min) return min;
    if (x > max) return max;
    return x;
}


// Common Headers

#include "Vec3.h"
#include "Ray.h"
