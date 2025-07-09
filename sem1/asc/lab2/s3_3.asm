bits 32 ; assembling for the 32 bits architecture

; declare the EntryPoint (a label defining the very first instruction of the program)
global start        

; declare external functions needed by our program
extern exit               ; tell nasm that exit exists even if we won't be defining it
import exit msvcrt.dll    ; exit is a function that ends the calling process. It is defined in msvcrt.dll
                          ; msvcrt.dll contains exit, printf and all the other important C-runtime specific functions

extern printf
import printf msvcrt.dll

; a, b, c, d word
; (b+b+d)-(c+a)
segment data use32 class=data
    a dw 8
    b dw 4
    c dw 3
    d dw 17
    r resw 1
    format db "%hd",0xD,0xA
    ; ...

segment code use32 class=code
    start:
        mov ax, [b]
        add ax, [b]
        add ax, [d] ; ax = b+b+d

        mov bx, [c]
        add bx, [a] ; bx = c+a

        sub ax, bx ; r = ax = (b+b+d)-(c+a)
        mov [r], ax

        push word [r]
        push format
        call [printf]

        ; exit(0)
        push    dword 0      ; push the parameter for exit onto the stack
        call    [exit]       ; call exit to terminate the program