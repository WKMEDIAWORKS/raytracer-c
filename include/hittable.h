#ifndef HITTABLE_H
#define HITTABLE_H

#include "ray.h"
#include <stdbool.h>

typedef struct hittable hittable;

typedef struct {
    point3 p;
    vec3 normal;
    double t;
} hit_record;

struct hittable{
    bool (*hit)(const hittable* self, const ray* r, double tmin, double tmax, hit_record* rec);
    //usage hittable* obj = (hittable*)&s;
};
#endif