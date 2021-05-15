#include "vector.h"
#include <assert.h>
#include <pmmintrin.h>
#include <stdio.h>
#include <time.h>

vector_t new_vector(size_t size) {
    vector_t vec = malloc(sizeof(struct vector_s) + sizeof(vec_val) * size);

    if (vec) {
        vec->size = size;
    }

    return vec;
}

void destroy_vector(vector_t vec) {
    free(vec);
}

// unsafe
vec_val scalar_product_vector(const vector_t v1, const vector_t v2) {
    assert(v1->size == v2->size);

    vec_val scalar = 0;

    for (size_t i = 0; i < v1->size; i++) {
        vec_val cur = 0;
        cur = (v1->vec[i] * v2->vec[i]);

        scalar += cur;
    }

    return scalar;
}

vec_val scalar_product_sse_vector(const vector_t v1, const vector_t v2) {
    vec_val total = 0;

    for (size_t i = 0; i < v1->size; i++) {
        vec_val cur = 0;
        __asm__(
            "movss %1, %%xmm0\n\t"
            "movss %2, %%xmm1\n\t"
            "mulss %%xmm0, %%xmm1\n\t"
            "movss %%xmm1, %0\n\t"
            : "=m" (cur)
            : "m"  (v1->vec[i]), "m"  (v2->vec[i])
        );

        total += cur;
    }

    return total;
}

int randomize_vector(vector_t v) {
    if (v == NULL) {
        return 1;
    }

    srand(time(NULL));

    for (size_t i = 0; i < v->size; i++) {
        v->vec[i] = (float)(rand() % RAND_TOP);
    }

    return 0;
}
