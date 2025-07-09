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
        mov ecx, (l1+2)/3
        jecxz next

    loop1:
        mov al, [s1+esi]
        mov [d+edi], al
        add esi, 3
        inc edi
        loop loop1

    next:
        mov ecx, l2
        mov esi, l2-1
        jecxz after

    loop2:
        mov al, [s2+esi]
        mov [d+edi], al
        dec esi
        inc edi
        loop loop2

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