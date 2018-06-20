#include <iostream>
#include "ray.h"
#include "sphere.h"
#include "hitable_list.h"
#include "float.h"

vec3 color(const ray &r, hitable *world)
{
    // First check if ray hits hitable object
    hit_record rec; 
    if (world->hit(r, 0.0, MAXFLOAT, rec)) {
        return 0.5*vec3(rec.normal.x()+1, rec.normal.y()+1, rec.normal.z()+1);
    } else { 
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
    int nx = 200;
    int ny = 100;
    std::cout << "P3\n"
              << nx << " " << ny << "\n255" << std::endl;
    // Specification of camera and the quad
    vec3 lower_left_corner(-2.0, -1.0, -1.0);
    vec3 horizontal(4.0, 0.0, 0.0);
    vec3 vertical(0.0, 2.0, 0.0);
    vec3 origin(0.0, 0.0, 0.0);

    hitable *list[2];
    list[0] = new sphere(vec3(0, 0, -1), 0.5);
    list[1] = new sphere(vec3(0, -100.5, -1), 100);

    hitable *world = new hitable_list(list, 2);

    for (int j = ny - 1; j >= 0; j--)
    {
        for (int i = 0; i < nx; i++)
        {
            // Getting UV coordinates
            float u = float(i) / float(nx);
            float v = float(j) / float(ny);
            // Create corresponding ray
            ray r(origin, lower_left_corner + u * horizontal + v * vertical);
            // Get color where ray is hitting quad
            vec3 col = color(r, world);
            float ir = int(255.99 * col[0]);
            float ig = int(255.99 * col[1]);
            float ib = int(255.99 * col[2]);

            std::cout << ir << " " << ig << " " << ib << std::endl;
        }
    }
}
