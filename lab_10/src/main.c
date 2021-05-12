#include <stdlib.h>
#include <stdio.h>
#include "vector.h"

int main(void ) {
    vector_t v1 = new_vector(4);
    vector_t v2 = new_vector(4);

    randomize_vector(v1);
    randomize_vector(v2);

    vec_val res = scalar_product_vector(v1, v2);

    printf("res = %f\n", res);

    destroy_vector(v1);
    destroy_vector(v2);

    return 0;
}
