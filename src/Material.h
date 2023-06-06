#pragma once

#include "Utils.h"

struct HitInfo;

class Material
{
public:
    virtual bool Scatter(const Ray& rayIn, const HitInfo& hit, Color& attenuation, Ray& scattered) const = 0;
};


class Lambertian : public Material
{
public:
    Lambertian(const Color& albedo) : albedo(albedo) {}


    // Methods

    virtual bool Scatter(const Ray& rayIn, const HitInfo& hit, Color& attenuation, Ray& scattered) const override
    {
        Vec3 scatterDirection = hit.normal + RandomUnitVector();

        // Catch degenerate scatter direction
        if (scatterDirection.NearZero())
            scatterDirection = hit.normal;

        scattered = Ray(hit.p, scatterDirection);
        attenuation = albedo;
        return true;
    }

public:
    Color albedo;
};


class Metal : public Material
{
public:
    Metal(const Color& albedo, double fuzz) : albedo(albedo), fuzz(fuzz) {}


    // Methods

    virtual bool Scatter(const Ray& rayIn, const HitInfo& hit, Color& attenuation, Ray& scattered) const override
    {
        Vec3 reflected = Reflect(UnitVector(rayIn.direction), hit.normal);
        scattered = Ray(hit.p, reflected + fuzz * RandomInUnitSphere());
        attenuation = albedo;
        return (Dot(scattered.direction, hit.normal) > 0);
    }

public:
    Color albedo;
    double fuzz;
};
