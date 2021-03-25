.186
extrn newline:near

STK  SEGMENT PARA STACK 'STACK'
        DB      300h DUP (0)
STK  ENDS

DSEG SEGMENT PARA PUBLIC 'DATA'
        input_clm_str       db "Input column number: $"
        input_row_str       db "Input row number: $"
        input_matrix_str    db "Input matrix:", 13, 10, '$'
        row                 db ?
        clm                 db ?
        max_row             db 9
        max_clm             db 9
        matrix              db 9 * 9 dup (0F1h)
        curr_clm            db ?
        curr_row            db ?

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
    mov dh, 0

    input_matrix_out:
        mov al, dh
        mul max_row
        mov bx, ax
        mov si, 0
        mov cx, 0
        input_matrix_inner:
            mov ah, 1
            int 21h
            sub ax, '0'

            mov matrix[bx][si], al
            
            inc cl
            inc si
            cmp cl, clm
        jb input_matrix_inner

        pusha
        call newline
        popa
    
    inc dh
    cmp dh, row
    jb input_matrix_out

    ret
input_matrix endp

find_clm_sum proc
    assume ds:DSEG

    mov dh, 0 ; i
    mov cx, 0 ; sum

    mov ax, 0
    mov al, curr_clm
    mov si, ax

    while_row:
        mov ax, 0
        mov al, dh
        mul max_row
        mov bx, ax

        mov ax, 0
        mov al, matrix[bx][si]
        add cx, ax

        inc dh
        cmp dh, row ; while ch < cl
    jb while_row

    ret
find_clm_sum endp

del_clm proc near
    mov dh, 0 ; i

    while_del_clm:
        
        mov curr_clm, dh

        push dx
        call find_clm_sum
        pop dx
        

        mov al, cl
        mov dl, 3

        div dl

        cmp ah, 0
        je delete_column

        inc dh
        cmp dh, clm
    jb while_del_clm


    ret
    delete_column:
        call shift_column
        ret
del_clm endp

shift_column proc near
    mov dx, 0
    mov cx, 0

    shift_clm_out:
        mov al, dh
        mul max_row
        mov bx, ax

        mov cl, curr_clm
        mov si, cx
        shift_clm_int:
            push ax
            xor ax, ax

            mov al, matrix[bx][si]
            
            push dx
            mov di, si
            inc di

            mov dl, matrix[bx][di]
            mov matrix[bx][si], dl

            pop dx

            mov matrix[bx][di], al

            pop ax

            inc si
            inc cl
            cmp cl, clm
        jb shift_clm_int

        inc dh
        cmp dh, row
    jb shift_clm_out

    dec clm

    ret
shift_column endp

print_matrix proc near
    mov bl, 0
    mov dh, 0

    pr_matrix_out:
        mov cl, 0

        mov al, dh
        mul max_row
        mov bx, ax

        mov si, 0

        pr_matrix_inner:
            push dx
            mov dl, matrix[bx][si]
            add dl, '0'
            mov ah, 2
            int 21h

            mov dl, ' '
            int 21h

            pop dx
            
            inc si
            inc cl
            cmp cl, clm
        jb pr_matrix_inner
    
        call newline
        ; mov dl, 10
        ; int 21h
        
        inc dh
        cmp dh, row
    jb pr_matrix_out

    ret

print_matrix endp
main:
    mov ax, DSEG
    mov ds, ax

    mov dx, offset input_row_str
    mov ah, 09h
    int 21h

    call input_row
    call newline

    mov dx, offset input_clm_str
    mov ah, 09h
    int 21h

    call input_clm
    call newline
    call newline

    mov dx, offset input_matrix_str
    mov ah, 09h
    int 21h

    call input_matrix

    call del_clm

    ; call newline
    ; call find_clm_sum

    call print_matrix

    mov ah, 4ch
    int 21h

CSEG ends
end main
