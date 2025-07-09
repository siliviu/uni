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

; a + b / c - d * 2 - e unsigned
segment code use32 class=code
    start:
        ; unsigned
       mov al, [b]
       mov ah, 0
       mov dx, 0
       div word [c]

       mov bx, ax

       mov al, 2
       mul byte [d]

       sub bx, ax
       mov cx, 0 ; cx bx = b/c - d*2

       mov ax, word [a]
       mov dx, word [a+2]
       add ax, bx
       adc dx, cx

       push dx
       push ax
       pop eax
    
       mov edx, 0
       sub eax, dword [e]
       sbb edx, dword [e+4]

       mov [x], eax
       mov [x+4], edx

        ; exit(0)
        push    dword 0      ; push the parameter for exit onto the stack
        call    [exit]       ; call exit to terminate the program