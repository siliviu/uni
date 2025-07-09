bits 32 ; assembling for the 32 bits architecture

; declare the EntryPoint (a label defining the very first instruction of the program)
global start        

; declare external functions needed by our program
extern exit               ; tell nasm that exit exists even if we won't be defining it
import exit msvcrt.dll    ; exit is a function that ends the calling process. It is defined in msvcrt.dll
                          ; msvcrt.dll contains exit, printf and all the other important C-runtime specific functions

extern printf
import printf msvcrt.dll

; a, b, c, d byte
; (c+d)-(a+d)+b
segment data use32 class=data
    a db 3
    b db 4
    c db 17
    d db 8
    r resb 1
    printr dw 0
    format db "%hhd", 0xD, 0xA
    ; ...

segment code use32 class=code
    start:
        mov al, [c]
        add al, [d] ; al = c+d
        
        mov ah, [a]
        add ah, [d] ; ah = a+d
        
        sub al, ah ; al = (c+d)-(a+d)
        
        add al, [b] ; r = al = (c+d)-(a+d)+b
        mov [r], al

        mov [printr], al
        push word [printr]
        push format
        call [printf]

        ; exit(0)
        push    dword 0      ; push the parameter for exit onto the stack
        call    [exit]       ; call exit to terminate the program