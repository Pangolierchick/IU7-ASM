project('lab_10', 'c', default_options: ['c_std=c99'])

incdir = include_directories('vector')

google_bench = dependency('benchmark')

subdir('vector')

exe = executable('main', ['./src/main.c'], dependencies: [google_bench, vec_lib])
