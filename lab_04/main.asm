public string
EXTRN input_string:far

STK  SEGMENT PARA STACK 'STACK'
        DB      200h DUP (0)
STK  ENDS

DSEG SEGMENT PARA PUBLIC 'DATA'
        hello_string db "Input string: $"
	string db 26                    ; max num of ch
               db ?                     ; num of chars entered by users
               db 26 dup("$")           ; user inputted string
        result_string db "4th char is: $"

DSEG ENDS

CSEG segment para public 'CODE'
        assume CS:CSEG, DS:DSEG, SS:STK


r_and_n proc near                       ; print \r\n
        mov ah, 2
        mov dl, 13
        int 21h

        mov ah, 2
        mov dl, 10
        int 21h
        
        ret
r_and_n endp

main:
        mov ax, DSEG
        mov ds, ax
        mov dx, offset hello_string             ; Вывод приглашения на ввод
        mov ah, 09h
        int 21h

        call input_string                       ; Ввод строки

; =================================
        call r_and_n                            ; Перенос строки
        mov ax, DSEG
        mov ds, ax
        mov dx, offset result_string            ; Вывод сообщения о результате
        mov ah, 09h
        int 21h
; =================================

        mov ah, 2
        mov al, [string + 5]            ; Получение 4 символа строки
        mov dl, al

        int 21h

        mov ah, 4ch
        int 21h

CSEG ends

END main
