bits 32

global start        

extern exit               
import exit msvcrt.dll    

extern printf
import printf msvcrt.dll

; A byte string S is given. Obtain in the string D the set of the elements of S.
segment data use32 class=data
    s db 1,4,2,4,8,2,1,1
    l equ $-s
    d times l db 0
    format db "%hd "

segment code use32 class=code
    start:
        mov esi, 0
        mov edi, 0
        mov ecx, l
        jecxz final

    loop1:
        mov al, [s+esi]
        push ecx
        push esi

        mov ecx, edi
        jecxz place_element
        mov esi, 0

        loop2:
            cmp al, [d+esi]
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
        mov esi, 0

    print:
        push ecx
        
        movzx ax, byte [d+esi]
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