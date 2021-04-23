section .text
global __memmove
bits 64


__memmove:
    mov rax, rdi

    ; dest < src
    cmp rdi, rsi

    je .done

    ; dest == src
    jb .fast

    ; dest >= src + num
    mov rcx, rsi
    add rcx, rdx
    cmp rdi, rcx

    jae .fast
        ; inverting copy direction
        std

        ; num of copies
        mov rcx, rdx

        dec rdx
        add rsi, rdx
        add rdi, rdx

        rep movsb

        cld
    ret
    
    .fast:
        ; std copy
        mov rcx, rdx
        rep movsb
    
    .done:
        ret
