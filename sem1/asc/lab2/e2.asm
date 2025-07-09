bits 32 ; assembling for the 32 bits architecture

; declare the EntryPoint (a label defining the very first instruction of the program)
global start        

; declare external functions needed by our program
extern exit               ; tell nasm that exit exists even if we won't be defining it
import exit msvcrt.dll    ; exit is a function that ends the calling process. It is defined in msvcrt.dll
                          ; msvcrt.dll contains exit, printf and all the other important C-runtime specific functions

; our data is declared here (the variables needed by our program)
; a - byte, b - word
segment data use32 class=data
a db 10
b dw 40
    ; ...

; (b / a * 2 + 10) * b - b * 15;
; our code starts here
segment code use32 class=code
    start:
        ; b/a
        mov ax, [b]
        div byte [a] ; al = ax/a=b/a. ah=ax%a=b%a

        ; ... * 2
        mov ah, 2
        mul ah ; ax = al * ah

        ; ... + 10
        add ax, 10 ; ax

        ; ... * b
        mul word [b] ; dx ax 
        
        ; move to ebx
        push dx
        push ax
        pop ebx

        ; b * 15
        mov ax, [b]
        mov dx, 15
        mul dx       ; dx ax

        ; move to eax
        push dx
        push ax
        pop eax

        ; ... - b*15
        sub ebx, eax


        ; exit(0)
        push    dword 0      ; push the parameter for exit onto the stack
        call    [exit]       ; call exit to terminate the program