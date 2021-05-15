#include <benchmark/benchmark.h>
extern "C" {
    #include "vector.h"
}

static void bench_default_scalar(benchmark::State& state) {
    const size_t iters = 10000;

    vector_t v1 = new_avectorf32(8);
    vector_t v2 = new_avectorf32(8);

    randomize_vector(v1);
    randomize_vector(v2);

    for (auto _ : state) {
        for (size_t i = 0; i < iters; i++) {
            auto res = scalar_product_vector(v1, v2);
        }
    }

    destroy_vector(v1);
    destroy_vector(v2);
}

static void bench_sse_scalar(benchmark::State& state) {
    const size_t iters = 10000;

    vector_t v1 = new_avectorf32(8);
    vector_t v2 = new_avectorf32(8);

    randomize_vector(v1);
    randomize_vector(v2);

    for (auto _ : state) {
        for (size_t i = 0; i < iters; i++) {
            auto res = scalar_product_sse_vector(v1, v2);
        }
    }

    destroy_vector(v1);
    destroy_vector(v2);
}

static void bench_sse_scalar2(benchmark::State& state) {
    const size_t iters = 10000;

    vector_t v1 = new_avectorf32(8);
    vector_t v2 = new_avectorf32(8);

    randomize_vector(v1);
    randomize_vector(v2);

    for (auto _ : state) {
        for (size_t i = 0; i < iters; i++) {
            auto res = scalar_product_sse_vector2(v1, v2);
        }
    }

    destroy_vector(v1);
    destroy_vector(v2);
}

BENCHMARK(bench_default_scalar);
BENCHMARK(bench_sse_scalar);
BENCHMARK(bench_sse_scalar2);

BENCHMARK_MAIN();
