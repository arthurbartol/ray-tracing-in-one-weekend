#pragma once

#include <vector>
#include <memory>
#include "Hittable.h"

using std::shared_ptr;
using std::make_shared;

class HittableList : public Hittable
{
public:
    HittableList() {}
    HittableList(shared_ptr<Hittable> object)
    {
        Add(object);
    }


    // Methods

    void Clear()
    {
        objects.clear();
    }

    void Add(shared_ptr<Hittable> object)
    {
        objects.push_back(object);
    }

    virtual bool Hit(const Ray& ray, double tMin, double tMax, HitInfo& hit) const override;

public:
    std::vector<shared_ptr<Hittable>> objects;
};


bool HittableList::Hit(const Ray& ray, double tMin, double tMax, HitInfo& hit) const
{
    HitInfo tempHit;
    bool hitAnything = false;
    double closestSoFar = tMax;

    for (const shared_ptr<Hittable> object : objects)
    {
        if (object->Hit(ray, tMin, closestSoFar, tempHit))
        {
            hitAnything = true;
            closestSoFar = tempHit.t;
            hit = tempHit;
        }
    }

    return hitAnything;
}
