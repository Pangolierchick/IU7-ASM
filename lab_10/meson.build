project('lab_10', ['c', 'cpp'], default_options: ['c_std=c99', 'cxx_std=c++17'])

incdir = include_directories('vector')

google_bench = dependency('benchmark')

subdir('vector')

exe = executable('main', ['./src/main.c'], dependencies: [vec_lib])

benchmark_exe = executable('vector_bench', ['./src/benchmark.cpp'], dependencies: [google_bench, vec_lib])
