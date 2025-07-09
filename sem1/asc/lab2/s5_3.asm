bits 32 ; assembling for the 32 bits architecture

; declare the EntryPoint (a label defining the very first instruction of the program)
global start        

; declare external functions needed by our program
extern exit               ; tell nasm that exit exists even if we won't be defining it
import exit msvcrt.dll    ; exit is a function that ends the calling process. It is defined in msvcrt.dll
                          ; msvcrt.dll contains exit, printf and all the other important C-runtime specific functions

extern printf
import printf msvcrt.dll

; a, b, c, d - byte, e, f, g, h - word
; (e+f) * g
segment data use32 class=data
    e dw 12
    f dw 5
    g dw 10
    r resd 1
    format db "%d", 0xD, 0xA
    ; ...

segment code use32 class=code
    start:
        mov ax, [e]
        add ax, [f] ; ax = e+f

        mul word [g] ; dx ax = (e+f)*g
       
        push dx
        push ax
        pop dword [r] ; r = (e+f)*g

        ; or pop eax
        ;    mov [r], eax

        push dword [r]
        push format
        call [printf]

        ; exit(0)
        push    dword 0      ; push the parameter for exit onto the stack
        call    [exit]       ; call exit to terminate the program