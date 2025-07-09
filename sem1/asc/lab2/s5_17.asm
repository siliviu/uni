bits 32 ; assembling for the 32 bits architecture

; declare the EntryPoint (a label defining the very first instruction of the program)
global start        

; declare external functions needed by our program
extern exit               ; tell nasm that exit exists even if we won't be defining it
import exit msvcrt.dll    ; exit is a function that ends the calling process. It is defined in msvcrt.dll
                          ; msvcrt.dll contains exit, printf and all the other important C-runtime specific functions

; a, b, c, d - byte, e, f, g, h - word
; h/a+(2+b)+f/d-g/c
segment data use32 class=data
    a db 7
    b db 2
    c db 3
    d db 4
    e dw 100
    f dw 48
    g dw 21
    h dw 32
    r resb 1
    ; ...

segment code use32 class=code
    start:
        mov ax, [h]
        div byte [a] ; al = h/a

        mov bl, [b]
        add bl, 2 ; bl = 2 + b
        
        add bl, al ; bl = h/a+(2+b)
        
        mov ax, [f]
        div byte [d] ; al = f/d

        add bl, al ; bl = h/a+(2+b)+f/d

        mov ax, [g]
        div byte [c] ; al = g/c
        
        sub bl, al ; r = bl = h/a+(2+b)+f/d-g/c
        mov [r], bl

        ; exit(0)
        push    dword 0      ; push the parameter for exit onto the stack
        call    [exit]       ; call exit to terminate the program