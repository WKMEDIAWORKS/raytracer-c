#ifndef COLOR_H
#define COLOR_H

#include "vec3.h"

#include <stdio.h>

typedef vec3 color;

void write_color(FILE *out, const color *pixel_color) {
    double r = getX(pixel_color);
    double g = getY(pixel_color);
    double b = getZ(pixel_color);

    int rbyte = (int)255.999 * r;
    int gbyte = (int)255.999 * g;
    int bbyte = (int)255.999 * b;

    fprintf(out, "%d %d %d\n", rbyte, gbyte, bbyte);
}

#endif
