#pragma once

#include "Utils.h"

class Material;

struct HitInfo
{
    Vec3 p;
    Vec3 normal;
    shared_ptr<Material> ptrMaterial;
    double t;
    bool frontFace;

    void SetFaceNormal(const Ray& ray, const Vec3& outwardNormal)
    {
        frontFace = Dot(ray.direction, outwardNormal) < 0;
        normal = frontFace ? outwardNormal : -outwardNormal;
    }
};

class Hittable
{
public:
    virtual bool Hit(const Ray& ray, double tMin, double tMax, HitInfo& hit) const = 0;
};
