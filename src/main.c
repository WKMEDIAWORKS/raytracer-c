#include "../include/rtweekend.h"
#include "../include/hittable.h"
#include "../include/hittable_list.h"
#include "../include/sphere.h"

#include <stdbool.h>

// double hit_sphere(const point3* center, double radius, const ray* r) {

//         vec3 ray_org = ray_origin(r);
//         vec3 ray_dir = ray_direction(r);

//         vec3 oc = vec3_sub(center, &ray_org);
//         double dir_length_squared = vec3_length_squared(&ray_dir);
//         double oc_length_squared = vec3_length_squared(&oc);

//         double a = dir_length_squared;
//         double h = vec3_dot(&ray_dir, &oc);
//         double c =  oc_length_squared - radius*radius;

//         double discriminant = h*h - a*c;
//         if(discriminant < 0) {
//             return -1.0;
//         }
//         else {
//             return ((h - sqrt(discriminant)) / a);
//         }
//     }

color ray_color(const ray* r, const hittable* world) {
     hit_record rec;
     if(world->hit(world, r, 0, infinity, &rec)) {
        color c = (color){.e = {1,1,1}};
        vec3 nAddC = vec3_add(&rec.normal, &c);
        return vec3_scale(0.5, &nAddC);
     }
     vec3 ray_dir = r->dir;

    vec3 unit_direction = vec3_unit_vector(&ray_dir);
    double a = 0.5*(getY(&unit_direction) + 1.0);
    vec3 opA = vec3_scale(1.0-a, &(color){.e = {1.0, 1.0, 1.0}});
    vec3 opB = vec3_scale(a, &(color){.e = {0.5, 0.7, 1.0}});

    return vec3_add(&opA, &opB);
}
int main(void) {
    //image
    double aspect_ratio = 16.0/9.0;

    int image_width = 400;
    double double_img_wdth = (double)image_width;
    int image_height = (int)(image_width / aspect_ratio);
    if(image_height < 1) {
        image_height = 1;
    }
    double double_img_hgt = (double)image_height;

    //world

    hittable_list world;
    hittable_list_init(&world);
    //usage hittable* obj = (hittable*)&s;
    sphere s1 = make_sphere((point3){.e = {0,0,-1}}, 0.5);
    sphere s2 = make_sphere((point3){.e = {0,-100.5,-1}}, 100);

    hittable* obj1 = (hittable*)&s1;
    hittable* obj2 = (hittable*)&s2;
    hittable* obj3 = (hittable*)&world;



    hittable_list_add(&world, obj1);
    hittable_list_add(&world, obj2);

    //camera
    double focal_length = 1.0;
    double viewport_height = 2.0;
    double viewport_width = viewport_height * ((double)(image_width)/image_height);
    point3 camera_center = vec3_zero();

    //calculate the vectors across the horizontal and down the vertical viewport edges.
    vec3 viewport_u = vec3_three(viewport_width, 0.0, 0.0);
    vec3 viewport_u_copy = viewport_u;
    vec3 viewport_v = vec3_three(0.0, -viewport_height, 0.0);
    vec3 viewport_v_copy = viewport_v;

    //calculate the horizontal and verticval delta vectors from pixel to pixel.

    vec3 pixel_delta_u = vec3_scale(1.0/ image_width, &viewport_u);
    vec3 pixel_delta_v = vec3_scale(1.0/ image_height, &viewport_v);
    
    // Calculate the location of the upper left pixel.

    vec3 viewport_upper_left =
    vec3_sub(
        &camera_center,
        &(vec3){0.0, 0.0, focal_length}
    );

    vec3 half_u = vec3_scale(0.5, &viewport_u);
    vec3 half_v = vec3_scale(0.5, &viewport_v);
    vec3 add_delta_uv = vec3_add(&pixel_delta_u, &pixel_delta_v);

    viewport_upper_left =
    vec3_sub(&viewport_upper_left, &half_u);

    viewport_upper_left =
    vec3_sub(&viewport_upper_left, &half_v);

    vec3 half_pixel =
    vec3_scale(0.5, &add_delta_uv);

    vec3 pixel00_loc =
    vec3_add(&viewport_upper_left, &half_pixel);


    //image headers
    printf("P3\n");
    printf("%d ", image_width);
    printf("%d", image_height);
    printf("\n255\n");

    //main image
    for(int i = 0; i < image_height; i++) {
        fprintf(stderr, "\rScan lines remaining: %d", (image_height-i));
        for(int j = 0; j < image_width; j++) {
            // vec3 pixel_color = vec3_three((double)j/(image_width-1), (double)i/(image_height-1), 0);
            vec3 j_mul_pxlu = vec3_scale(j, &pixel_delta_u);
            vec3 i_mul_pxlv = vec3_scale(i, &pixel_delta_v);

            vec3 pixel_00loc_add_pxlu = vec3_add(&pixel00_loc, &j_mul_pxlu);
            
            vec3 pixel_center = vec3_add(&pixel_00loc_add_pxlu, &i_mul_pxlv);
            vec3 ray_direction = vec3_sub(&pixel_center, &camera_center);
            ray r = ray_create(camera_center, ray_direction);

            color pixel_color = ray_color(&r, obj3);
            write_color(stdout, &pixel_color);
        }
    }
    fprintf(stderr, "\rDone.              \n");
}