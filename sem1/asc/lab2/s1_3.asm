bits 32 ; assembling for the 32 bits architecture

; declare the EntryPoint (a label defining the very first instruction of the program)
global start        

; declare external functions needed by our program
extern exit               ; tell nasm that exit exists even if we won't be defining it
import exit msvcrt.dll    ; exit is a function that ends the calling process. It is defined in msvcrt.dll
                          ; msvcrt.dll contains exit, printf and all the other important C-runtime specific functions

extern printf
import printf msvcrt.dll

; 128 + 128
segment data use32 class=data
    a dw 128
    b dw 128
    r resw 1
    format db "%hd", 0xD, 0xA
    ; ...

segment code use32 class=code
    start:
        mov ax, [a]
        add ax, [b]
        mov [r], ax ; r = ax = a + b

        push word [r]
        push format
        call [printf]

        ; exit(0)
        push    dword 0      ; push the parameter for exit onto the stack
        call    [exit]       ; call exit to terminate the program