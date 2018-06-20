#include <iostream>
#include "ray.h"

/*
 * Equation of a sphere centered at the origin is
 *
 *      x*x + y*y + z*z = R*R
 *
 * where R is the radius.
 *
 * if the sphere is not centered at the origin but
 * instead in C = (a,b,c) then
 *
 *      (x-a)*(x-a) + (y-b)*(y-b) + (z-c)*(z-c) = R*R
 *
 * Note that the vector from C to a point p is (p - C).
 *
 *      p ----> C                              <=>
 *      (p[0] - C[0], p[1] - C[1], p[2]-C[2])  <=>
 *      ((x-a), (x-b), (x-c))
 *
 * and dot((p-C), (p-C)) = (x-a)*(x-a) + (y-b)*(y-b) + (z-c)*(z-c)
 *
 * That gives the formula
 *
 *      dot((p-C), (p-C)) = R*R
 *
 * it reads: "any point p that satisfies this equation is on the sphere"
 *
 * Therefore we are looking for any value t that satisfies the formula.
 *
 *      dot((A+t*B-C), (A+t*B-c)) = R*R
 *
 * This can be expanded to
 *
 *      t*t*dot(B,B) + 2*t*dot(B,A-C) + dot(A-C, A-C) - R*R = 0
 *
 * This gives a quadric equation with two roots
 *
 *      t1 = -b + sqrt(b*b - 4*c)
 *      t2 = -b - sqrt(b*b - 4*c)
 *
 * Where a is the first term  -> dot(B,B)
 * Where b is the second term -> 2 * dot(B, A-C)
 * Where c is the third term  -> dot(A-C, A-C) - R * R
 * */

float hit_sphere(const vec3& center, float radius, const ray& r) {
    // (A-C) -> distance from center_sphere to origin
    vec3 oc = r.origin() - center;
    float a = dot(r.direction(), r.direction());
    float b = 2.0 * dot(oc, r.direction());
    float c = dot(oc, oc) - radius*radius;
    float discriminant = b*b - 4*a*c; // if discriminant is positive 
                                      // there is space for two roots
    if (discriminant < 0.0) {     // meaning ray is hitting sphere 
        return -1.0;
    }
    else {
        // std::cout << "discriminant: " << discriminant << std::endl;
        // getchar();
        return (-b - sqrt(discriminant)) / (2.0*a);
    }

    // if (discriminant > epsilon) {     
    //     std::cout << "discriminant: " << discriminant << std::endl;
    //     getchar();
    // }
    // return (discriminant > epsilon);
}

vec3 color(const ray& r) {
    // First check if ray hits sphere
    float t  = hit_sphere(vec3(0,0,-1), 0.5, r);
    if (t > 0.0) {
        // Take the normal of sphere as color
        vec3 normal = unit_vector(r.point_at(t) - vec3(0,0,-1));
        normal = 0.5 * vec3(normal.x()+1, normal.y()+1, normal.z()+1);
        // std::cout << "Normal: " << normal.x() << " " << normal.y() << " " << normal.z() << std::endl;
        return normal;
    }

    // if (hit_sphere(vec3(0,0,-1), 0.5, r))
    //     return vec3(1,0,0);

    // Getting normalized direction of ray
    vec3 dir = unit_vector(r.direction());

    // Scale y-component of dir to 0 - 1
    t = 0.5 * (dir.y() + 1.0);

    // when t = 1 -> blue, when t = 0 -> white
    // In between is a blend (this is called a linear interpolation (lerp))
    return (1.0 - t) * vec3(1.0, 1.0, 1.0) + t * vec3(0.5, 0.7, 1.0);
}

int main() {
    int nx = 200;
    int ny = 100;
    std::cout << "P3\n" << nx << " " << ny << "\n255" << std::endl;
    // Specification of camera and the quad
    vec3 lower_left_corner(-2.0, -1.0, -1.0);
    vec3 horizontal(4.0, 0.0, 0.0);
    vec3 vertical(0.0, 2.0, 0.0);
    vec3 origin(0.0, 0.0, 0.0);

    for (int j = ny-1; j >= 0; j--) {
        for (int i = 0; i < nx; i++) {
            // Getting UV coordinates
            float u = float(i) / float(nx);
            float v = float(j) / float(ny);
            // Create corresponding ray
            ray r(origin, lower_left_corner + u*horizontal + v*vertical);
            // Get color where ray is hitting quad
            vec3 col = color(r);
            float ir = int(255.99 * col[0]);
            float ig = int(255.99 * col[1]);
            float ib = int(255.99 * col[2]);

            std::cout << ir << " " << ig << " " << ib << std::endl;
        }
    }
}

