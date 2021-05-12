#include <cstdio>
#include <cmath>

int main() {
    const double pi1 = 3.14;
    const double pi2 = 3.141596;

    printf("=============== sin(pi) ===============\n");
    printf("3.14     ... %lf\n", sin(pi1));
    printf("3.141596 ... %lf\n", sin(pi2));
    double asm_res = 0;
    __asm__(
        "fldpi   \n\t"
        "fsin    \n\t"
        "fstpl %0\n\t"
        :: "m" (asm_res)
    );

    printf("FPU_PI   ... %lf\n", asm_res);

    printf("\n============== sin(pi/2) ==============\n");
    printf("3.14     ... %lf\n", sin(pi1 / 2));
    printf("3.141596 ... %lf\n", sin(pi2 / 2));

    const int two = 2;

    __asm__(
        "filds %1\n\t"
        "fldpi\n\t"
        "fdivp\n\t"
        "fsin\n\t"
        "fstpl %0\n\t"
        : "=m" (asm_res)
        : "m" (two)
    );

    printf("FPU_PI   ... %lf\n", asm_res);

    return 0;
}
