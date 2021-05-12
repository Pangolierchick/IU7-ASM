clang -S asm_code.c -O0 -fno-vectorize -m80387 -mno-sse -o 80387.s
clang -S asm_code.c -O0 -fno-vectorize -mno-80387 -mno-sse -o no80387.s
