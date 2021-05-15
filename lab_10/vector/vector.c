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

// allocate's vector with float allignment
vector_t new_avectorf32(size_t size) {

    size_t allignment = sizeof(float);
    size_t a_size = (size % allignment) ? (size + (allignment - size % allignment)) : size;

    vector_t vec = calloc(1, sizeof(struct vector_s) + sizeof(vec_val) * a_size);
    
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

vec_val scalar_product_sse_vector2(const vector_t v1, const vector_t v2) {
    vec_val total = 0;

    for (size_t i = 0; i < v1->size - 1; i += 2) {
        vec_val cur = 0;
        __asm__(
            "movss %1, %%xmm0\n\t"
            "movss %2, %%xmm1\n\t"
            "movss %3, %%xmm2\n\t"
            "movss %4, %%xmm3\n\t"
            "mulss %%xmm0, %%xmm1\n\t"
            "mulss %%xmm2, %%xmm3\n\t"
            "addss %%xmm3, %%xmm1\n\t"
            "movss %%xmm1, %0\n\t"
            : "=m" (cur)
            : "m"  (v1->vec[i]), "m"  (v2->vec[i]), "m"  (v1->vec[i + 1]), "m"  (v2->vec[i + 1])
        );

        total += cur;
    }

    return total;
}

vec_val scalar_product_sse_vector(const vector_t v1, const vector_t v2) {
    vec_val total = 0;

    __asm__(
        "xorps %%xmm2, %%xmm2\n\t"
        :
        :
        );

    for (size_t i = 0; i < v1->size; i += 4) {
        __asm__(
            "movups (%0), %%xmm0\n\t"
            "movups (%1), %%xmm1\n\t"
            "mulps %%xmm1, %%xmm0\n\t"
            "haddps %%xmm0, %%xmm0\n\t"
            "addps %%xmm0, %%xmm2\n\t"

            :
            : "r"  (v1->vec + i), "r"  (v2->vec + i)
        );
    }

    __asm__(
        "haddps %%xmm2, %%xmm2\n\t"
        "movss %%xmm2, %0\n\t"
        : "=m"(total)
    );

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
