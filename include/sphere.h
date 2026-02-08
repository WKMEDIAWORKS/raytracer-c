#ifndef SPHERE_H
#define SPHERE_H

#include "hittable.h"
#include "vec3.h"
#include <math.h>

typedef struct {
    hittable base;
    point3 center;
    double radius;
} sphere;


bool sphere_hit(const hittable* self, const ray* r, double tmin, double tmax, hit_record* rec) {
    const sphere* s = (const sphere*) self;

    vec3 oc = vec3_sub(&s->center, &r->orig);
    double a = vec3_length_squared(&r->dir);
    double h = vec3_dot(&r->dir, &oc);
    double c = vec3_length_squared(&oc) - s->radius * s->radius;

    double discriminant = h*h - a*c;
    if(discriminant < 0) return false;

    double sqrtd = sqrt(discriminant);

    double root = (h-sqrtd) / a;
    if(root <= tmin || root >= tmax) {
        root = (h+sqrtd) / a;
        if(root <= tmin || root >= tmax) {
            return false;
        }
    }

        rec->t = root;
        rec->p = ray_at(r, root);
        // vec3 pSubC = vec3_sub(rec->p, s->center);
        // rec->normal = vec3_divide_inplace(&pSubC, s->radius);
        vec3 pToC = vec3_sub(&rec->p, &s->center);

        vec3 outward_normal = vec3_divide_inplace(&pToC, s->radius);

        set_face_normal(rec, r, &outward_normal);

        return true;

}

sphere make_sphere(point3 center, double radius) {
    sphere s;
    s.base.hit = sphere_hit;
    s.center = center;
    s.radius = radius < 0 ? 0 : radius;

    return s;
}

#endif