#include <iostream>
#include "sphere.h"
#include "hitable_list.h"
#include "float.h"
#include "camera.h"
#include "material.h"

vec3 color(const ray &r, hitable *world, int depth)
{
    // First check if ray hits hitable object
    hit_record rec;
    if (world->hit(r, 0.0001, MAXFLOAT, rec)) // if ray hits a surface
    {
        ray scattered;
        vec3 attenuation;
        if (depth < 50 && rec.mat_ptr->scatter(r, rec, attenuation, scattered))
        {
            return attenuation * color(scattered, world, depth + 1);
        }
        else
        {
            return vec3(0,0,0); 
        }
    }
    else
    {
        // Getting normalized direction of ray
        vec3 dir = unit_vector(r.direction());

        // Scale y-component of dir to 0 - 1
        float t = 0.5 * (dir.y() + 1.0);

        // when t = 1 -> blue, when t = 0 -> white
        return (1.0 - t) * vec3(1.0, 1.0, 1.0) + t * vec3(0.5, 0.7, 1.0);
    }
}

int main()
{
    int nx = 400;
    int ny = 200;
    int ns = 100; // nr of samples for anti-aliasing
    std::cout << "P3\n"
              << nx << " " << ny << "\n255" << std::endl;

    hitable *list[4];
    list[0] = new sphere(vec3(0, 0, -1),      0.5, new lambertian(vec3(0.8, 0.3, 0.3)));
    list[1] = new sphere(vec3(0, -100.5, -1), 100, new lambertian(vec3(0.8, 0.8, 0.0)));
    list[2] = new sphere(vec3(1, 0, -1),      0.2, new metal(vec3(0.8, 0.6, 0.6), 0.3));
    list[3] = new sphere(vec3(-1, 0.3, -1),    0.4, new metal(vec3(0.8, 0.8, 0.4), 1.0));

    hitable *world = new hitable_list(list, 4);

    camera cam;
    for (int j = ny - 1; j >= 0; j--)
    {
        for (int i = 0; i < nx; i++)
        {
            vec3 col(0, 0, 0);
            for (int s = 0; s < ns; s++)
            {
                // Getting UV coordinates
                float u = float(i + drand48()) / float(nx);
                float v = float(j + drand48()) / float(ny);
                // Create corresponding ray
                ray r = cam.get_ray(u, v);
                // Get color where ray is hitting quad
                col += color(r, world, 0);
            }
            col /= float(ns); // get average color from samples ns

            // Compensate for image viewers gamma correction
            col = vec3(sqrt(col[0]), sqrt(col[1]), sqrt(col[2]));
            float ir = int(255.99 * col[0]);
            float ig = int(255.99 * col[1]);
            float ib = int(255.99 * col[2]);

            std::cout << ir << " " << ig << " " << ib << std::endl;

        }
    }
}
