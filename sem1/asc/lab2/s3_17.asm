bits 32 ; assembling for the 32 bits architecture

; declare the EntryPoint (a label defining the very first instruction of the program)
global start        

; declare external functions needed by our program
extern exit               ; tell nasm that exit exists even if we won't be defining it
import exit msvcrt.dll    ; exit is a function that ends the calling process. It is defined in msvcrt.dll
                          ; msvcrt.dll contains exit, printf and all the other important C-runtime specific functions

; a, b, c, d word
; a+a-b-c-(d+d)
segment data use32 class=data
    a dw 17
    b dw 4
    c dw 3
    d dw 8
    r resw 1
    ; ...

segment code use32 class=code
    start:
        mov ax, [a]
        add ax, [a]
        sub ax, [b]
        sub ax, [c] ; ax = a+a-b-c
        
        mov bx, [d]
        add bx, [d] ; bx = d+d

        sub ax, bx ; r=ax=(a+a-b-c)-(d+d) 
        mov [r], ax

        ; exit(0)
        push    dword 0      ; push the parameter for exit onto the stack
        call    [exit]       ; call exit to terminate the program