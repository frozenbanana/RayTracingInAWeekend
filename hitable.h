#ifndef HITABLEH
#define HITABLEH

#include "ray.h"

// When hit save relevant data here
struct hit_record {
    float t;
    vec3 point;
    vec3 normal;
};

// All hitable object must have this function.
// It determines if a ray is hitting an object
// and if yes, fills a hit_record rec
class hitable {
    public:
        virtual bool hit(const ray& r, float t_min, float t_max, hit_record& rec) const = 0;
};

#endif