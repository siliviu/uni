bits 32 ; assembling for the 32 bits architecture

; declare the EntryPoint (a label defining the very first instruction of the program)
global start        

; declare external functions needed by our program
extern exit               ; tell nasm that exit exists even if we won't be defining it
import exit msvcrt.dll    ; exit is a function that ends the calling process. It is defined in msvcrt.dll
                          ; msvcrt.dll contains exit, printf and all the other important C-runtime specific functions

; a, b, c - byte, d - word
; 300-(5*(d-2*a)-1)
segment data use32 class=data
    a db 7
    d dw 60
    two db 2
    five dw 5
    r resd 1
    ; ...

segment code use32 class=code
    start:
        mov al, [a] 
        mul byte [two] ; ax=2*a

        mov bx, ax ; bx=2*a

        mov ax, [d]
        sub ax, bx ; ax=d-2*a 

        mul word [five] ; dx ax = 5*(d-2*a)

        push dx
        push ax
        pop eax ; eax = dx ax

        sub eax, 1 ; eax = 5*(d-2*a)-1

        mov ebx, 300
        sub ebx, eax ;  r = ebx = 300 - 5*(d-2*a)-1
        mov [r], ebx

        ; exit(0)
        push    dword 0      ; push the parameter for exit onto the stack
        call    [exit]       ; call exit to terminate the program