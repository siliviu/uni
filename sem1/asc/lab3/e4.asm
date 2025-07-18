bits 32 ; assembling for the 32 bits architecture

; declare the EntryPoint (a label defining the very first instruction of the program)
global start        

; declare external functions needed by our program
extern exit               ; tell nasm that exit exists even if we won't be defining it
import exit msvcrt.dll    ; exit is a function that ends the calling process. It is defined in msvcrt.dll
                          ; msvcrt.dll contains exit, printf and all the other important C-runtime specific functions

; a double word; b, c byte
segment data use32 class=data
    a dd 12345678h
    b db 2
    c dw 15
    d db 200
    e dq 80

    x dq 0

    ; ...

; a + b / c - d * 2 - e signed
segment code use32 class=code
    start:
        ;unsigned
        mov al, [b]
        cbw
        cwd
        idiv word [c]

        mov bx, ax
        
        ; ...
        
        ; exit(0)
        push    dword 0      ; push the parameter for exit onto the stack
        call    [exit]       ; call exit to terminate the program