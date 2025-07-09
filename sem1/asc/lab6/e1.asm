; ex4

bits 32

global start        

extern exit               
import exit msvcrt.dll    

extern printf
import printf msvcrt.dll

segment data use32 class=data
    s1 db 7, 3, 9, 1, 5
    s2 db 2, 4, 6, 8, 10
    l EQU s2-s1
    d times l db 0
    format db "%hd "


; Se dau 2 siruri de numere intregi s1 si s2 de lungimi egale.
; Se cere sirul de numere intregi d obtinut astfel:
; - d[i] = s1[i] - s2[i], daca s1[i] > s2[i]
; - d[i] = s2[i] - s1[i], altfel.
segment code use32 class=code
    start:
        mov ecx, l
        mov esi, 0
        jecxz final

    for:
        mov al, [s1+esi]
        mov dl, [s2+esi]
        cmp al, dl
        jb smaller
        sub al, dl
        mov [d+esi], al
        jmp finish_loop

        smaller:
            sub dl, al
            mov [d+esi], dl

        finish_loop:
            inc esi
            loop for

    mov ecx, l
    mov esi, 0
    jecxz final

    print:
        push ecx

        movsx ax, byte [d+esi]
        push eax
        push format
        call [printf]
        add esp, 8

        inc esi
        pop ecx
        loop print

    final:
        push dword 0   
        call [exit]