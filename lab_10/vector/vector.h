#pragma once

#include <stdlib.h>

#define RAND_TOP        10000

typedef float vec_val;

typedef struct vector_s {
    size_t size;
    vec_val vec[];
} *vector_t;

void destroy_vector(vector_t vec);
vector_t new_vector(size_t size);
int randomize_vector(vector_t v);
vec_val scalar_product_vector(vector_t v1, vector_t v2);
