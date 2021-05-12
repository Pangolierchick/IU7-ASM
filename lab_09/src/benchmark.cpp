#include <iostream>
#include <cmath>
#include <benchmark/benchmark.h>


static void float_fpu_auto(float a, float b, float c, float d) {
    c = a + b;
    d = a * b;
}

static void double_fpu_auto(double a, double b, double c, double d) {
    c = a + b;
    d = a * b;
}

static void long_double_fpu_auto(long double a, long double b, long double c, long double d) {
    c = a + b;
    d = a * b;
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

static void bench_float_fpu_auto(benchmark::State& state) {
    for (auto _ : state) {
        for (int i = 0; i < 10000; i++) {
            float_fpu_auto(M_PI, M_LN2, 0, 0);
        }
    }
}

static void bench_double_fpu_auto(benchmark::State& state) {
    for (auto _ : state) {
        for (int i = 0; i < 10000; i++) {
            double_fpu_auto(M_PI, M_LN2, 0, 0);
        }
    }
}

static void bench_long_double_fpu_auto(benchmark::State& state) {
    for (auto _ : state) {
        for (int i = 0; i < 10000; i++) {
            long_double_fpu_auto(M_PI, M_LN2, 0, 0);
        }
    }
}

static void bench_float_fpu_asm(benchmark::State& state) {
    for (auto _ : state) {
        for (int i = 0; i < 10000; i++) {
            float_fpu_asm(M_PI, M_LN2, 0, 0);
        }
    }
}

static void bench_double_fpu_asm(benchmark::State& state) {
    for (auto _ : state) {
        for (int i = 0; i < 10000; i++) {
            double_fpu_asm(M_PI, M_LN2, 0, 0);
        }
    }
}


BENCHMARK(bench_float_fpu_auto);
BENCHMARK(bench_double_fpu_auto);
BENCHMARK(bench_long_double_fpu_auto);

BENCHMARK(bench_float_fpu_asm);
BENCHMARK(bench_double_fpu_asm);

BENCHMARK_MAIN();
