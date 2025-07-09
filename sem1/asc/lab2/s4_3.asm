bits 32 ; assembling for the 32 bits architecture

; declare the EntryPoint (a label defining the very first instruction of the program)
global start        

; declare external functions needed by our program
extern exit               ; tell nasm that exit exists even if we won't be defining it
import exit msvcrt.dll    ; exit is a function that ends the calling process. It is defined in msvcrt.dll
                          ; msvcrt.dll contains exit, printf and all the other important C-runtime specific functions

extern printf
import printf msvcrt.dll

; a, b, c - byte, d - word
; (-1+d-2*(b+1))/a
segment data use32 class=data
    a db 7
    b db 9
    d dw 60
    two db 2
    r resb 1
    printr dw 0
    format db "%hhd", 0xD, 0xA
    ; ...

segment code use32 class=code
    start:
        mov al, [b]
        add al, 1 ; al = b+1

        mul byte [two] ; bx = ax = 2*(b+1)
        mov bx, ax

        mov ax, -1
        add ax, [d]
        sub ax, bx ; ax = -1+d-2*(b+1)

        div byte [a] ; r = al = (-1+d-2*(b+1))/a
        mov [r], al

        mov [printr], al
        push word [printr]
        push format
        call [printf]

        ; exit(0)
        push    dword 0      ; push the parameter for exit onto the stack
        call    [exit]       ; call exit to terminate the program