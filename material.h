#ifndef MATERIALH
#define MATERIALH

#include "ray.h"
#include "hitable.h"

vec3 reflect(const vec3 &v, const vec3 &n) {
    return v - 2 * dot(v, n) * n; // perfect reflection
}

vec3 random_in_unit_sphere() {
    vec3 p;
    do {
        // Generate a vector p = [[-1,1], [-1,1], [-1,1]]
        p = 2.0 * vec3(drand48(), drand48(), drand48()) - vec3(1, 1, 1);
    } while (p.squared_length() >= 1.0);
    return p;
}

class material
{
  public:
    virtual bool scatter(const ray &r_in, const hit_record &rec, vec3 &attenuation, ray &scattered) const = 0;
};

class metal : public material
{
  public:
    metal(const vec3 &a, float f) : albedo(a) { if (f < 1) fuzz = f; else fuzz = 1;}

    // Reflect ray. Leave color as albedo
    virtual bool scatter(const ray &r_in, const hit_record &rec, vec3 &attenuation, ray &scattered) const {
        vec3 refl = reflect(unit_vector(r_in.direction()), rec.normal);
        // Fuzz shrinks the directional vector making the reflection blurry
        scattered = ray(rec.point, fuzz * refl);
        attenuation = albedo;
            return (dot(scattered.direction(), rec.normal) > 0);
    }

    float fuzz;
    vec3 albedo;
};

class lambertian : public material
{
  public:
    lambertian(const vec3 &a) : albedo(a) {}

    // Reflect ray in a scattered manner. Leave color as albedo
    virtual bool scatter(const ray &r_in, const hit_record &rec, vec3 &attenuation, ray &scattered) const {
        vec3 refl = rec.normal + random_in_unit_sphere(); // reflect it slightly
        scattered = ray(rec.point, refl);
        attenuation = albedo;
        return true;
    }

    vec3 albedo;
};

#endif