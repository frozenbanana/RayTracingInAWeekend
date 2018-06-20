#ifndef SPHEREH
#define SPHEREH

#include "hitable.h"

class sphere : public hitable
{
  public:
    sphere() {}
    sphere(vec3 cen, float r, material *m) : center(cen), radius(r), mat_ptr(m) {};
    virtual bool hit(const ray &r, float t_min, float t_max, hit_record &rec) const;
    vec3 center;
    float radius;
    material *mat_ptr;
};

bool sphere::hit(const ray &r, float t_min, float t_max, hit_record &rec) const
{
    // (A-C) -> distance from center_sphere to origin
    vec3 oc = r.origin() - center;
    float a = dot(r.direction(), r.direction());
    float b = 2.0 * dot(oc, r.direction());
    float c = dot(oc, oc) - radius * radius;
    float discriminant = b * b - 4 * a * c; // if discriminant is positive there is space for two roots
    if (discriminant > 0.0)
    {
        float t_temp = (-b - sqrt(discriminant)) / (2 * a);
        if (t_temp < t_max && t_temp > t_min)
        {
            rec.t = t_temp;
            rec.point = r.point_at(t_temp);
            rec.normal = (rec.point - center) / radius; // trick to normalize
            rec.mat_ptr = mat_ptr;
            return true;
        }

        t_temp = (-b + sqrt(discriminant)) / (2 * a);
        if (t_temp < t_max && t_temp > t_min)
        {
            rec.t = t_temp;
            rec.point = r.point_at(t_temp);
            rec.normal = (rec.point - center) / radius; // trick to normalize
            rec.mat_ptr = mat_ptr;
            return true;
        }
    }
    return false;
}
#endif