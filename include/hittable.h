#ifndef HITTABLE_H
#define HITTABLE_H

#include "ray.h"
#include <stdbool.h>

typedef struct hittable hittable;

typedef struct {
    point3 p;
    vec3 normal;
    double t;
    bool front_face;
} hit_record;

struct hittable{
    bool (*hit)(const hittable* self, const ray* r, double tmin, double tmax, hit_record* rec);
    //usage hittable* obj = (hittable*)&s;
};

void set_face_normal(hit_record* rec, const ray* r, const vec3* outward_normal) {
    vec3 ray_dir = ray_direction(r);
    rec->front_face = vec3_dot(&ray_dir, outward_normal) < 0;
    if(rec->front_face) {
        rec->normal = *outward_normal;
    }
}
#endif