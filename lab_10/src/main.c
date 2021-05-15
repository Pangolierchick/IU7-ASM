#include <stdlib.h>
#include <stdio.h>
#include "vector.h"

int main(void ) {
    vector_t v1 = new_avectorf32(12);
    vector_t v2 = new_avectorf32(12);

    // randomize_vector(v1);
    // randomize_vector(v2);

    for (size_t i = 0; i < v1->size; i++) {
        v1->vec[i] = i;
        v2->vec[i] = i;
    }

    vec_val res = scalar_product_vector(v1, v2);
    printf("res = %f\n", res);
    
    vec_val sse = scalar_product_sse_vector2(v1, v2);
    printf("res = %f\n", sse);

    destroy_vector(v1);
    destroy_vector(v2);

    return 0;
}
