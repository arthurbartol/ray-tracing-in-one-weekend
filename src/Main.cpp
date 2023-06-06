#include <iostream>

#include "Utils.h"
#include "Color.h"
#include "HittableList.h"
#include "Sphere.h"
#include "Camera.h"
#include "Material.h"


Color RayColor(const Ray& ray, const HittableList& world, int depth);


int main()
{
    // Image

    const double ASPECT_RATIO = 16.0 / 9.0;
    const int IMAGE_WIDTH = 1280;
    const int IMAGE_HEIGHT = static_cast<int>(IMAGE_WIDTH / ASPECT_RATIO);
    const int SAMPLES_PER_PIXEL = 100;
    const int MAX_DEPTH = 50;


    // World

    HittableList world;

    shared_ptr<Lambertian> groundMat = make_shared<Lambertian>(Color(0.8, 0.8, 0.0));
    shared_ptr<Lambertian> centerMat = make_shared<Lambertian>(Color(0.7, 0.3, 0.3));
    shared_ptr<Metal> leftMat = make_shared<Metal>(Color(0.8, 0.8, 0.8), 0.3);
    shared_ptr<Metal> rightMat = make_shared<Metal>(Color(0.8, 0.6, 0.2), 1.0);

    world.Add(make_shared<Sphere>(Vec3( 0.0, -100.5, -1.0), 100, groundMat));
    world.Add(make_shared<Sphere>(Vec3( 0.0, 0.0,    -1.0), 0.5, centerMat));
    world.Add(make_shared<Sphere>(Vec3(-1.0, 0.0,    -1.0), 0.5, leftMat));
    world.Add(make_shared<Sphere>(Vec3( 1.0, 0.0,    -1.0), 0.5, rightMat));


    // Camera

    Camera cam;


    // Render

    std::cout << "P3\n" << IMAGE_WIDTH << " " << IMAGE_HEIGHT << "\n255\n";

    for (int y = IMAGE_HEIGHT-1; y >= 0; y--)
    {
        std::cerr << "\rScanlines remaining: " << y << " " << std::flush;
        for (int x = 0; x < IMAGE_WIDTH; x++)
        {
            Color pixelColor(0.0, 0.0, 0.0);
            for (int s = 0; s < SAMPLES_PER_PIXEL; s++)
            {
                double u = (x + RandomDouble()) / (IMAGE_WIDTH - 1);
                double v = (y + RandomDouble()) / (IMAGE_HEIGHT - 1);

                Ray ray = cam.GetRay(u, v);
                pixelColor += RayColor(ray, world, MAX_DEPTH);
            }
            WriteColor(std::cout, pixelColor, SAMPLES_PER_PIXEL);
        }
    }

    std::cerr << "\nDone.\n";
}


Color RayColor(const Ray& ray, const HittableList& world, int depth)
{
    HitInfo hit;

    // If we've exceeded the ray bounce limit, no more light is gathered
    if (depth <= 0)
        return Color(0, 0, 0);

    if (world.Hit(ray, 0.001, _INFINITY, hit))
    {
        Ray scattered;
        Color attenuation;
        if (hit.ptrMaterial->Scatter(ray, hit, attenuation, scattered))
            return attenuation * RayColor(scattered, world, depth-1);
        return Color(0, 0, 0);
    }

    Vec3 unitDirection = UnitVector(ray.direction);
    double t = 0.5 * (unitDirection.y + 1.0);
    return (1.0 - t) * Color(1.0, 1.0, 1.0) + t * Color(0.5, 0.7, 1.0);
}
