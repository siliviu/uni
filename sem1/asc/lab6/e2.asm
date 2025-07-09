; ex3

bits 32

global start        

extern exit               
import exit msvcrt.dll    

extern printf
import printf msvcrt.dll

segment data use32 class=data
    s db 12h, 13h, 15h, 18h, 22h, 25h, 27h, 30h
    l EQU $-s
    s1 times l db 0
    s2 times l db 0
    format db "%hd ", 0x0   
    formatnl db 0xD, 0xA


; Se da un sir de numere intregi s.
; Se cere sa se determine sirurile de numere intregi:
; s1 - care contine doar numerele intregi pare din sirul s
; s2 - care contine doar numerele intregi impare din sirul s
segment code use32 class=code
    start:
        mov ecx, l
        mov esi, 0
        mov edi, 0
        mov edx, 0
        jecxz inter

    for:
        mov al, [s+esi]
        test al, 1
        jz even

        mov [s2+edi], al
        inc edi
        jmp finish_loop

        even:
            mov [s1+edx], al
            inc edx

        finish_loop:
            inc esi
            loop for

    inter:
        mov ecx, edx
        mov esi, 0
        jecxz final

    print1:
        push ecx

        movsx ax, byte [s1+esi]
        push eax
        push format
        call [printf]
        add esp, 8

        inc esi
        pop ecx
        loop print1

    next:
        push formatnl
        call [printf]
        add esp, 4

        mov ecx, esi
        mov esi, 0
        jecxz final

    print2:
        push ecx

        movsx ax, byte [s2+esi]
        push eax
        push format
        call [printf]
        add esp, 8

        inc esi
        pop ecx
        loop print2

    final:
        push dword 0   
        call [exit]