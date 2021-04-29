#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define IS_DONE(f) (f) ? "Done." : "Failed."

extern void _memmove(void *d, void *s, int l);

size_t strlen_asm64(const char *str) {
    size_t len = 0;

    __asm__(    
        "mov $0, %%al\n\t"
        "mov %1, %%rdi\n\t"
        "mov $-1, %%rcx\n\t"
        "repne scasb\n\t"
        "neg %%rcx\n\t"
        "sub $2, %%rcx\n\t"
        "mov %%rcx, %0\n\t"
        : "=r"(len)
        : "r"(str)
        : "%eax", "%ecx", "%rdi", "%al"
        );

    return len;
}

int strlen_asm32(const char *str) {
    int len = 0;

    __asm__(    
        "mov $0, %%al\n\t"
        "mov %1, %%rdi\n\t"
        "mov $0xffffffff, %%ecx\n\t"
        "repne scasb\n\t"
        "mov $0xffffffff, %%eax\n\t"
        "dec %%eax\n\t"
        "sub %%ecx, %%eax\n\t"
        "mov %%eax, %0"
        : "=r"(len)
        : "r"(str)
        : "%eax", "%ecx", "%rdi", "%al"
        );

    return len;
}

int main(void) {
    printf("\t\tBegin testing\n\n");

    const int butt_size = 100;

    char str[butt_size]      = "Hello, world!";
    char std_str[butt_size]  = "Hello, world!";
    char buff[butt_size]     = "12345";
    char std_buff[butt_size] = "12345";

    int len = 0;
    int std_len = 0;

    printf("\t\tTesting string len:\n\n");

    std_len = strlen(str);
    len = strlen_asm64(str);

    printf("1. %s", IS_DONE(std_len == len));
    printf("\t%d\t%d\n", std_len, len);

    std_len = strlen(str + 5);
    len = strlen_asm64(str + 5);

    printf("2. %s", IS_DONE(std_len == len));
    printf("\t%d\t%d\n", std_len, len);

    std_len = strlen(str + 13);
    len = strlen_asm64(str + 13);

    printf("3. %s", IS_DONE(std_len == len));
    printf("\t%d\t%d\n", std_len, len);

    printf("\t\tTesting memmove:\n\n");

    _memmove(buff, str, 10);
    memmove(std_buff, str, 10);

    printf("1. %s", IS_DONE(memcmp(buff, std_buff, 10) == 0));
    printf("\t%s\t%s\n", buff, std_buff);

    _memmove(str + 4, str, 10);
    memmove(std_str + 4, std_str, 10);

    printf("2. %s", IS_DONE(memcmp(str, std_str, 10) == 0));
    printf("\t%s\t%s\n", str, std_str);

    _memmove(str, str + 4, 10);
    memmove(std_str, std_str + 4, 10);

    printf("3. %s", IS_DONE(memcmp(str, std_str, 10) == 0));
    printf("\t%s\t%s\n", str, std_str);

    return 0;
}
