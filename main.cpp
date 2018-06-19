#include <iostream>
#include "ray.h"

vec3 color(const ray& r) {
    // Getting normalized direction of ray
    vec3 dir = unit_vector(r.direction());
    // Scale y-component of dir to 0 - 1
    float t = 0.5 * (dir.y() + 1.0);

    // when t = 1 -> blue, when t = 0 -> white
    // In between is a blend (this is called a linear interpolation (lerp))
    return (1.0 - t) * vec3(1.0, 1.0, 1.0) + t * vec3(0.5, 0.7, 1.0);
}
int main() {
    int nx = 200;
    int ny = 100;

    // Specification of camera and the quad
    vec3 origin(0.0, 0.0, 0.0);
    vec3 lower_left_corner(-2.0, -1.0, -1.0);
    vec3 horizontal(4.0, 0.0, 0.0);
    vec3 vertical(0.0, 2.0, 0.0);

    std::cout << "P3\n" << nx << " " << ny << "\n255" << std::endl;
    for (int j = ny-1; j >= 0; j--) {
        for (int i = 0; i < nx; i++) {
            // Getting UV coordinates
            float u = float(i)/ float(nx);
            float v = float(j) / float(ny);
            // Create corresponding ray
            ray r(origin, lower_left_corner + u*horizontal + v*vertical);
            // Get color where ray is hitting quad
            vec3 col = color(r);
            float ir = int((col[0]) * 255.99);
            float ig = int((col[1]) * 255.99);
            float ib = int((col[2]) * 255.99);
            std::cout << ir << " " << ig << " " << ib << std::endl;
        }
    }
}

