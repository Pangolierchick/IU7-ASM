#pragma once

#include <stdlib.h>

#define RAND_TOP 10000

typedef float vec_val;

typedef struct vector_s {
    size_t size;
    vec_val vec[];
} * vector_t;

extern void destroy_vector(vector_t vec);
extern vector_t new_vector(size_t size);
extern vector_t new_avectorf32(size_t size);

extern int randomize_vector(vector_t v);

extern vec_val scalar_product_vector(const vector_t v1, const vector_t v2);
extern vec_val scalar_product_sse_vector(const vector_t v1, const vector_t v2);
extern vec_val scalar_product_sse_vector2(const vector_t v1, const vector_t v2);
