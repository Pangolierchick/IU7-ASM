public input_string
EXTRN string: byte

CSEG segment para public 'CODE'
    assume CS:CSEG

input_string proc far
    mov ah, 0Ah
    mov dx, offset string ; inputting string
    int 21h
    
    mov si, offset string + 1
    mov cl, [ si ]
    xor ch, ch
    inc cx
    add si, cx
    mov al, '$'
    mov [ si ], al

    ret
input_string endp

CSEG ends
end
