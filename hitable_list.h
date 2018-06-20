#ifndef HITABLELISTH
#define HITABLELISTH

#include "hitable.h"

// A list of hitable objects
class hitable_list: public hitable {
    public:
        hitable_list() {}
        hitable_list(hitable **l, int n) {list = l; list_size = n;}
        virtual bool hit(const ray& r, float t_min, float t_max, hit_record& rec) const;
        hitable** list;
        int list_size;
};

// Returns true if anything is hit and fills the record with the closest hitable
bool hitable_list::hit(const ray& r, float t_min, float t_max, hit_record& rec) const {
    hit_record rec_temp;
    bool hit_anything = false;
    float closest_so_far = t_max;

    for(int i = 0; i < list_size; i++)
    {
        if (list[i]->hit(r, t_min, closest_so_far, rec_temp)) {
            hit_anything = true;
            closest_so_far = rec_temp.t;
            rec = rec_temp;
        }
    }

    return hit_anything; 
}

#endif