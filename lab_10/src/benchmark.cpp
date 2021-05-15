#include <benchmark/benchmark.h>


extern "C" {
    #include "vector.h"
}

static void bench_default_scalar(benchmark::State& state) {
    vector_t v1 = new_avectorf32(72);
    vector_t v2 = new_avectorf32(72);

    randomize_vector(v1);
    randomize_vector(v2);

    for (auto _ : state) {
        while (state.KeepRunning()) {
            benchmark::DoNotOptimize(
                scalar_product_vector(v1, v2)
            );
        }
    }

    destroy_vector(v1);
    destroy_vector(v2);
}

static void bench_sse_scalar(benchmark::State& state) {
    vector_t v1 = new_avectorf32(72);
    vector_t v2 = new_avectorf32(72);

    randomize_vector(v1);
    randomize_vector(v2);

    for (auto _ : state) {
        while (state.KeepRunning()) {
            benchmark::DoNotOptimize(
                scalar_product_sse_vector(v1, v2)
            );
        }
    }

    destroy_vector(v1);
    destroy_vector(v2);
}

static void bench_sse_scalar2(benchmark::State& state) {
    vector_t v1 = new_avectorf32(72);
    vector_t v2 = new_avectorf32(72);

    randomize_vector(v1);
    randomize_vector(v2);

    for (auto _ : state) {
        while (state.KeepRunning()) {
            benchmark::DoNotOptimize(
                scalar_product_sse_vector2(v1, v2)
            );
        }
    }

    destroy_vector(v1);
    destroy_vector(v2);
}

BENCHMARK(bench_default_scalar)->Arg(10000);
BENCHMARK(bench_sse_scalar)->Arg(10000);
BENCHMARK(bench_sse_scalar2)->Arg(10000);

BENCHMARK_MAIN();
