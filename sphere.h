#ifndef SPHEREH
#define SPHEREH

#include "hitable.h"
#include "vec3.h"

class sphere : public hitable
{
  public:
    sphere() {}
    sphere(vec3 cen, float r) : center(cen), radius(r) {};
    virtual bool hit(const ray &r, float t_min, float t_max, hit_record &rec) const;
    vec3 center;
    float radius;
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
            return true;
        }

        t_temp = (-b + sqrt(discriminant)) / (2 * a);
        if (t_temp < t_max && t_temp > t_min)
        {
            rec.t = t_temp;
            rec.point = r.point_at(t_temp);
            rec.normal = (rec.point - center) / radius; // trick to normalize
            return true;
        }
    }
    return false;
}
#endif