#include <assert.h>
#include <time.h>
#include "vector.h"

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
vec_val scalar_product_vector(vector_t v1, vector_t v2) {
    assert(v1->size == v2->size);

    vec_val scalar = 0;

    for (size_t i = 0; i < v1->size; i++) {
        scalar += (v1->vec[i] * v2->vec[i]);
    }

    return scalar;
}

int randomize_vector(vector_t v) {
    if (v == NULL) {
        return 1;
    }

    srand(time(NULL));

    for (size_t i = 0; i < v->size; i++) {
        v->vec[i] = (float) (rand() % RAND_TOP);
    }

    return 0;
}
