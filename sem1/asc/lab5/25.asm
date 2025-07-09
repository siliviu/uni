bits 32

global start        

extern exit               
import exit msvcrt.dll    

extern printf
import printf msvcrt.dll

segment data use32 class=data
    s1 db '+', '4', '2', 'a', '8', '4', 'X', '5'
    l1 equ $-s1
    s2 db 'a', '4', '5'
    l2 equ $-s2
    d times (l1+l2) db 0
    format db "%c"

segment code use32 class=code
    start:
        mov esi, 0
        mov edi, 0
        mov ecx, l1
        jecxz after

    loop1:
        mov al, [s1+esi]
        push ecx
        push esi

        mov ecx, l2
        jecxz place_element
        mov esi, 0

        loop2:
            cmp al, [s2+esi]
            je finish_loop
            inc esi
            loop loop2

        place_element:
            mov [d+edi], al
            inc edi
        
        finish_loop:
            pop esi
            pop ecx
            inc esi
            loop loop1


    after:
        mov ecx, edi
        jecxz final
        mov esi, 0

    print:
        push ecx
        
        mov al, [d+esi]
        push eax
        push format
        call [printf]
        add esp, 8

        inc esi
        pop ecx
        loop print

    final:
        push    dword 0   
        call    [exit]    