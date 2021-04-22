.MODEL TINY

CODE SEGMENT
    ASSUME CS:CODE, DS:CODE
    ORG 100H

MAIN:
    jmp install
    old_8h dd ?
    is_installed dw 1
    curr_time db 0
    speed db 1fh
    

my_int_handler proc
    push ax
    push bx
    push cx
    push dx

    push es
    push ds

    ;pushf

    mov ah, 02h
    int 1ah

    cmp dh, curr_time
    mov curr_time, dh
    
    je quit

    mov al, 0f3h
    out 60h, al

    mov al, speed
    out 60h, al 

    dec speed

    test speed, 1fh
    jz update_speed

    jmp quit

    update_speed:
        mov speed, 1fh

    quit:
     ;   popf
        pop ds
        pop es

        pop dx
        pop cx
        pop bx
        pop ax

        jmp cs:old_8h
my_int_handler endp

install proc 
    mov ax, 3508h
    int 21h

    cmp es:is_installed, 1
    je uninstall

    mov word ptr old_8h, bx
    mov word ptr old_8h + 2, es

    mov ax, 2508h
    mov dx, offset my_int_handler
    int 21h

    mov dx, offset installed_msg
    mov ah, 09h
    int 21h

    mov dx, offset install
    int 27h

install endp
    

uninstall proc
    push es
    push ds

    mov dx, word ptr es:old_8h
    mov ds, word ptr es:old_8h + 2
    mov ax, 2508h
    int 21h

    pop ds
    pop es
    
    mov al, 0f3h
    out 60h, al
    mov al, 0
    out 60h, al

    mov ah, 49h
    int 21h

    mov dx, offset uninstalled_msg
    mov ax, cs
    mov ds, ax
    mov ah, 09h
    int 21h

    mov ax, 4c00h
    int 21h

    uninstalled_msg db 'Uninstalled$'
    installed_msg   db 'Installed$'
uninstall endp

CODE ENDS
END MAIN
