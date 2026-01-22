#ifndef RAY_H
#define RAY_H

#include "vec3.h"

typedef struct {
    point3 orig;
    vec3 dir;
} ray;

static inline ray ray_default() {
    ray r;
    r.orig = (point3){0,0,0};
    r.dir = (vec3){0,0,0};
    return r;
}

static inline ray ray_create(point3 orig, vec3 dir) {
    ray r;
    r.orig = orig;
    r.dir = dir;
    return r;
}

//usage: const point3* p = ray_origin(&r);

static inline const point3 ray_origin(const ray* r) {
    return r->orig;
}

static inline const vec3 ray_direction(const ray* r) {
    return r->dir;
}

static inline point3 ray_at(const ray* r, double t) {
    vec3 scaled = vec3_scale(t, &r->dir);
    return vec3_add(&r->orig, &scaled);
}

#endif