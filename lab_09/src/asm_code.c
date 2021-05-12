#include <math.h>
#include <fenv.h> 
#include <stdio.h>

static void float_fpu_auto() {
    float a = M_PI;
    float b = M_LN2;

    float c = a + b;

    float d = a * b;
}

static void double_fpu_auto() {
    double a = M_PI;
    double b = M_LN2;

    double c = a + b;

    double d = a * b;
}

static void long_double_fpu_auto() {
    long double a = M_PI;
    long double b = M_LN2;

    long double c = a + b;

    long double d = a * b;
}

static void float_fpu_asm(float a, float b, float c, float d) {
    __asm__(
        "flds %2\n\t"
        "flds %3\n\t"
        "faddp \n\t"
        "fstps %0\n\t"
        "flds %2\n\t"
        "flds %3\n\t"
        "fmulp  \n\t"
        "fstps %1\n\t"
        : "=m" (c), "=m" (d)
        : "m" (a), "m" (b)
    );
}

static void double_fpu_asm(double a, double b, double c, double d) {
    __asm__(
        "fldl %2\n\t"
        "fldl %3\n\t"
        "faddp \n\t"
        "fstps %0\n\t"
        "fldl %2\n\t"
        "fldl %3\n\t"
        "fmulp  \n\t"
        "fstps %1\n\t"
        : "=m" (c), "=m" (d)
        : "m" (a), "m" (b)
    );
}

int main() {
    float_fpu_auto();
    double_fpu_auto();
    long_double_fpu_auto();

    float_fpu_asm(M_PI, M_LN2, 0, 0);
    double_fpu_asm(M_PI, M_LN2, 0, 0);

    return 0;
}
