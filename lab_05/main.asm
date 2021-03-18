extrn newline:near

STK  SEGMENT PARA STACK 'STACK'
        DB      200h DUP (0)
STK  ENDS

DSEG SEGMENT PARA PUBLIC 'DATA'
        input_clm_str db "Input column number: $"
        input_row_str db "Input row number: $"
        row db 'F'
        clm db 'F'
        matrix db 9 * 9 dup (255)

DSEG ENDS


CSEG segment para public 'CODE'
        assume CS:CSEG, DS:DSEG, SS:STK


input_row proc near
    mov ah, 01h
    int 21h

    sub ax, '0'
    mov row, al
    
    ret

input_row endp

input_clm proc near
    mov ah, 01h
    int 21h

    sub ax, '0'
    mov clm, al

    ret

input_clm endp

input_matrix proc near
    mov ax, DSEG
    mov ds, ax

    mov al, row
    mov bl, clm

    mul bl     ; getting size of matrix (row * clm)

    mov cx, ax ; number of iters to do
    mov dx, 0  ; sort of i in for loop
    mov si, offset matrix

    while_input:
        mov ah, 01h
        int 21h

        sub ax, '0'         ; from char to int
        mov [ si ], al      ; setting value to matrix

        inc dx              ; i++ actually
        inc si              ; getting next elem
        cmp dx, cx          
    jb while_input          ; while dx < cx

    ret
input_matrix endp


del_clm proc near
    mov al, row
    mov bl, clm

    mul bl     ; getting size of matrix (row * clm)

    mov cl, clm
    mov ch, row

    mov dl, 0
    mov dh, 0

    mov si, offset matrix
    while_row:
        mov dh, 0

        while_clm:
            push si
            
            cmp dl, row
        jb while_clm

        add si, row
        cmp dh, clm
    jb while_row

    mov si, offset matrix
    ret
del_clm endp

main:
    mov ax, DSEG
    mov ds, ax

    mov dx, offset input_clm_str
    mov ah, 09h
    int 21h

    call input_clm
    call newline

    mov dx, offset input_row_str
    mov ah, 09h
    int 21h

    call input_row
    call newline

    mov ah, 2
    mov dl, clm
    int 21h

    call newline

    mov ah, 2
    mov dl, row
    int 21h

    call newline
    call input_matrix

    mov ah, 4ch
    int 21h

CSEG ends
end main
