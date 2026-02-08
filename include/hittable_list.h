#ifndef HITTABLE_LIST_H
#define HITTABLE_LIST_H

#include "hittable.h"
#include <stddef.h>
#include <stdlib.h>

typedef struct hittable_list {
    hittable base;
    hittable** objects;
    size_t count;
    size_t capacity;
} hittable_list;

static bool hittable_list_hit(const hittable* self, const ray* r, double tmin, double tmax, hit_record* rec) {
    hittable_list* list = (hittable_list*)self;

    hit_record temp;

    bool hit_anything = false;
    double closest = tmax;

    for(size_t i = 0; i < list->count; ++i) {
        hittable* obj = list->objects[i];

        if(obj->hit(obj, r, tmin, closest, &temp)) {
            hit_anything = true;
            closest = temp.t;
            *rec = temp;
        }
    }

    return hit_anything;
}

void hittable_list_init(hittable_list* list) {
    list->base.hit = hittable_list_hit;
    list->objects = NULL;
    list->count = 0;
    list->capacity = 0;
}

void hittable_list_add(hittable_list* list, hittable* object) {
    if(list->count == list->capacity) {
        size_t new_cap = list->capacity == 0 ? 4 : list->capacity*2;
        list->objects = realloc(list->objects, new_cap * sizeof(hittable*));

        list->capacity = new_cap;
    }
    list->objects[list->count++] = object;
}

void hittable_list_clear(hittable_list* list) {
    list->count = 0;
}

void hittable_list_free(hittable_list* list) {
    free(list->objects);
    list->objects = NULL;
    list->count = 0;
    list->capacity = 0;
}

#endif