public newline

CSEG segment para public 'CODE'
    assume CS:CSEG

newline proc near                       ; print \r\n
        mov ah, 2
        mov dl, 13
        int 21h

        mov ah, 2
        mov dl, 10
        int 21h
        
        ret
newline endp

CSEG ends
end
