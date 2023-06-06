#pragma once

#include "Vec3.h"
#include "Hittable.h"

class Sphere : public Hittable
{
public:
    Sphere() {}
    Sphere(Vec3 center, double radius, shared_ptr<Material> ptrMaterial)
        : center(center), radius(radius), ptrMaterial(ptrMaterial) {}


    // Methods

    virtual bool Hit(const Ray& ray, double tMin, double tMax, HitInfo& hit) const override;

public:
    Vec3 center;
    double radius;
    shared_ptr<Material> ptrMaterial;
};


bool Sphere::Hit(const Ray& ray, double tMin, double tMax, HitInfo& hit) const
{
    Vec3 oc = ray.origin - center;

    double a = ray.direction.Length2();
    double halfb = Dot(oc, ray.direction);
    double c = oc.Length2() - (radius * radius);

    double discriminant = (halfb * halfb) - (a * c);
    if (discriminant < 0)
        return false;
    double sqrtDisc = sqrt(discriminant);

    // Find the nearest root that lies in the acceptable range
    double root = (-halfb - sqrtDisc) / a;
    if (root < tMin || root > tMax)
    {
        root = (-halfb + sqrtDisc) / a;
        if (root < tMin || root > tMax)
            return false;
    }

    hit.t = root;
    hit.p = ray.At(hit.t);
    Vec3 outwardNormal = (hit.p - center) / radius;
    hit.SetFaceNormal(ray, outwardNormal);
    hit.ptrMaterial = ptrMaterial;

    return true;
}
