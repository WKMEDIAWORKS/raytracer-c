#ifndef VEC3_H
#define VEC3_H

#include <math.h>
#include <stdio.h>

//vec3 struct
typedef struct {
    double e[3];  
}vec3;

typedef vec3 point3;

//call this function to use vec3 without providing any arguments
vec3 vec3_zero(void) {
    return (vec3){ .e = {0.0, 0.0, 0.0} };
}

//call this function to provide the values of e1, e2, and e3 respectively

vec3 vec3_three(double e1, double e2, double e3) {
    return (vec3){ .e = {e1, e2, e3} };
}

double getX(const vec3 *v) {
    return v->e[0];
}

double getY(const vec3 *v) {
    return v->e[1];
}

double getZ(const vec3 *v) {
    return v->e[2];
}

vec3 vec3_negate (vec3 e) {
    return (vec3) {-e.e[0], -e.e[1], -e.e[2]};
}

double vec3_getE_atI(vec3 e, int i) {
    return e.e[i];
}

//usage:
//*vec3_get_loc(&v, 0) = 5.0
//returns a location of e[i]
static inline double* vec3_get_loc(vec3 *v, int i) {
    return &v->e[i];
}

static inline vec3* vec3_add_inplace(vec3 *a, vec3 *b) {
    a->e[0] += b->e[0];
    a->e[1] += b->e[1];
    a->e[2] += b->e[2];
    return a;
}

static inline vec3* vec3_multiply_inplace(vec3 *a, double t) {
    a->e[0] *= t;
    a->e[1] *= t;
    a->e[2] *= t;

    return a;
}

static inline vec3 vec3_divide_inplace(vec3 *a, double t) {
    double inv = 1.0 / t;
    a->e[0] *= inv;
    a->e[1] *= inv;
    a->e[2] *= inv;
    
    return *a;
}

static inline double vec3_length_squared(const vec3 *v) {
    double sqred = v->e[0]*v->e[0] +
                   v->e[1]*v->e[1] +
                   v->e[2]*v->e[2];
                   return sqred;
}

double vec3_length(const vec3 *v) {
    return sqrt(vec3_length_squared(v));
}

//usage:
//vec3_print(stdout, &v);
static inline void vec3_print(FILE *out, const vec3 *v) {
    fprintf(out, "%f %f %f", v->e[0], v->e[1], v->e[2]);
}

//vector utility functions

static inline vec3 vec3_add(const vec3* a, const vec3* b) {
    return (vec3){a->e[0]+ b->e[0], a->e[1] + b->e[1], a->e[2] + b->e[2]};
}

static inline vec3 vec3_sub(const vec3* a, const vec3* b) {
    return (vec3){a->e[0]- b->e[0], a->e[1] - b->e[1], a->e[2] - b->e[2]};
}

static inline vec3 vec3_mul(const vec3* a, const vec3* b) {
    return (vec3){a->e[0] * b->e[0], a->e[1] * b->e[1], a->e[2] * b->e[2]};
}

static inline vec3 vec3_scale(double t, const vec3* a) {
    return (vec3){a->e[0] * t, a->e[1] * t, a->e[2] * t};
}


// vec3 vec3_scale(const vec3* a, double t) {
//     return (vec3){a->e[0] * t, a->e[1] * t, a->e[2] * t};
// }

static inline double vec3_dot(const vec3* a, const vec3* b) {
    return a->e[0] * b->e[0] + a->e[1] * b->e[1] + a->e[2] * b->e[2];
} 

static inline vec3 vec3_cross(const vec3* a, const vec3* b) {
    return (vec3){
        (a->e[1] * b->e[2] - a->e[2] * b->e[1]),
        (a->e[2] * b->e[0] - a->e[0] * b->e[2]),
        (a->e[0] * b->e[1] - a->e[1] * b->e[0])
    };
}

static inline vec3 vec3_unit_vector(const vec3* a) {
    double length = vec3_length(a);
    return (vec3){a->e[0]/length, a->e[1]/length, a->e[2]/length};
}

static inline vec3 vec3_add_t(const vec3* a, double t) {
    return (vec3){a->e[0]+t, a->e[1]+t, a->e[2]+t};
}

#endif














