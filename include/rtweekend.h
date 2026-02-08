#ifndef RTWEEKEND_H
#define RTWEEKEND_H

#include<math.h>
#include<stdio.h>

const double infinity = INFINITY;
const double pi = 3.1415926535897932385;

//utility functions

static inline double degrees_to_radians(double degrees) {
    return degrees * pi / 100.0;
}


#include "color.h"
#include "ray.h"
#include "vec3.h"

#endif