project('lab_10', ['c', 'cpp'], default_options: ['c_std=c99', 'c++_std=c++17'])

incdir = include_directories('vector')

google_bench = dependency('benchmark')
subdir('vector')

if google_bench.found()
    benchmark_exe = executable('vector_bench', ['./src/benchmark.cpp'], dependencies: [google_bench, vec_lib])
endif


exe = executable('main', ['./src/main.c'], dependencies: [vec_lib])

