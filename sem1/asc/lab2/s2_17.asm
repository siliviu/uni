bits 32 ; assembling for the 32 bits architecture

; declare the EntryPoint (a label defining the very first instruction of the program)
global start        

; declare external functions needed by our program
extern exit               ; tell nasm that exit exists even if we won't be defining it
import exit msvcrt.dll    ; exit is a function that ends the calling process. It is defined in msvcrt.dll
                          ; msvcrt.dll contains exit, printf and all the other important C-runtime specific functions

; a, b, c, d byte
; (a+a-c)-(b+b+b+d)
segment data use32 class=data
    a db 17
    b db 4
    c db 3
    d db 8
    r resb 1
    ; ...

segment code use32 class=code
    start:
        mov al, [a]
        add al, [a]
        sub al, [c] ; al = a+a+c
        
        mov ah, [b]
        add ah, [b]
        add ah, [b]
        add ah, [d] ; ah = b+b+d
        
        sub al, ah ; r=al=(a+a+c)-(b+b+d)
        mov [r], al

        ; exit(0)
        push    dword 0      ; push the parameter for exit onto the stack
        call    [exit]       ; call exit to terminate the program