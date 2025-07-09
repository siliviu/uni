bits 32

global start        

extern exit               
import exit msvcrt.dll    

extern printf
import printf msvcrt.dll

segment data use32 class=data
    s1 db 'a', 'b', 'c', 'd', 'e', 'f'
    l1 equ $-s1
    s2 db '1', '2', '3', '4', '5'
    l2 equ $-s2
    d times (l1+l2) db 0
    format db "%c"

segment code use32 class=code
    start:
        mov esi, 0
        mov edi, 0

        cmp esi, l2
        jae next

    loop2:
        mov al, [s2+esi]
        mov [d+edi], al
        inc edi
        add esi, 2
        cmp esi, l2
        jae next
        jmp loop2

    next:
        mov esi, 1
        cmp esi, l1
        jae after
    
    loop1:
        mov al,[s1+esi]
        mov [d+edi], al
        inc edi
        add esi, 2
        cmp esi, l1
        jae after
        jmp loop1

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