#pragma once

#include <iostream>
#include <cmath>

using std::sqrt;

class Vec3
{
public:
    Vec3() : x(0), y(0), z(0) {}
    Vec3(double x, double y, double z) : x(x), y(y), z(z) {}


    // Operator Overloadings

    Vec3 operator-() const
    {
        return Vec3(-x, -y, -z);
    }

    Vec3& operator+=(const Vec3& v)
    {
        x += v.x;
        y += v.y;
        z += v.z;
        return *this;
    }

    Vec3& operator*=(const double t)
    {
        x *= t;
        y *= t;
        z *= t;
        return *this;
    }

    Vec3& operator/=(const double t)
    {
        return *this *= 1 / t;
    }


    // Methods

    double Length() const
    {
        return sqrt(Length2());
    }

    double Length2() const
    {
        return (x * x) + (y * y) + (z * z);
    }

    bool NearZero() const
    {
        // Return true if the vector is close to zero in all dimensions
        const auto s = 1e-8;
        return (fabs(x) < s) && (fabs(y) < s) && (fabs(z) < s);
    }

    inline static Vec3 Random()
    {
        return Vec3(RandomDouble(), RandomDouble(), RandomDouble());
    }

    inline static Vec3 Random(double min, double max)
    {
        return Vec3(RandomDouble(min, max), RandomDouble(min, max), RandomDouble(min, max));
    }

public:
    double x, y, z;
};


// Type aliase

using Color = Vec3;


// Utility Functions

inline std::ostream& operator<<(std::ostream& out, const Vec3& v)
{
    return out << v.x << " " << v.y << " " << v.z;
}

inline Vec3 operator+(const Vec3& u, const Vec3& v)
{
    return Vec3(u.x + v.x, u.y + v.y, u.z + v.z);
}

inline Vec3 operator-(const Vec3& u, const Vec3& v)
{
    return Vec3(u.x - v.x, u.y - v.y, u.z - v.z);
}

inline Vec3 operator*(const Vec3& u, const Vec3& v)
{
    return Vec3(u.x * v.x, u.y * v.y, u.z * v.z);
}

inline Vec3 operator*(double t, const Vec3& v)
{
    return Vec3(t * v.x, t * v.y, t * v.z);
}

inline Vec3 operator*(const Vec3& v, double t)
{
    return t * v;
}

inline Vec3 operator/(Vec3 v, double t)
{
    return (1 / t) * v;
}

inline double Dot(const Vec3& u, const Vec3& v)
{
    return (u.x * v.x) + (u.y * v.y) + (u.z * v.z);
}

inline Vec3 Cross(const Vec3& u, const Vec3& v)
{
    return Vec3(
        u.y * v.z - u.z * v.y,
        u.z * v.x - u.x * v.z,
        u.x * v.y - u.y * v.x
    );
}

inline Vec3 UnitVector(Vec3 v)
{
    return v / v.Length();
}

inline Vec3 RandomInUnitSphere()
{
    while (true)
    {
        Vec3 p = Vec3::Random(-1, 1);
        if (p.Length2() >= 1)
            continue;
        return p;
    }
}

inline Vec3 RandomUnitVector()
{
    return UnitVector(RandomInUnitSphere());
}

inline Vec3 RandomInHemisphere(const Vec3& normal)
{
    Vec3 inUnitSphere = RandomInUnitSphere();
    if (Dot(inUnitSphere, normal) > 0.0)    // In the same hemisphere as the normal
        return inUnitSphere;
    else
        return -inUnitSphere;
}

inline Vec3 Reflect(const Vec3& v, const Vec3& n)
{
    return v - 2 * Dot(v, n) * n;
}
