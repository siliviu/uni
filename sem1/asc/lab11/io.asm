bits 32

global read, print
extern exit,fopen,fscanf,fclose,printf

import fopen msvcrt.dll
import fscanf msvcrt.dll
import fclose msvcrt.dll
import printf msvcrt.dll

segment data use32 class=data
    a resd 1
    mode db "r", 0
    name db "numere.txt", 0
    format db "%d ", 0
    newline db 13,10,0

segment code use32 class=code
    read:
        push ebp
        mov ebp, esp

        push ebx
        push esi
        push edi

        mov edi, [ebp + 8]
        cld

        push mode
        push name
        call [fopen]
        add esp, 8
        mov ebx, eax

        .while:
            push a
            push format
            push ebx
            call [fscanf]
            add esp, 12

            cmp eax, 0
            jle .final

            mov esi, a
            movsd

            jmp .while
        
        .final:
            push ebx
            call [fclose]
            add esp, 4
            
            mov eax, edi
            
            pop edi
            pop esi
            pop ebx
            
            mov esp, ebp
            pop ebp

            ret 4

    print:
        push ebp
        mov ebp, esp

        push ebx
        push esi
        push edi
       
        mov esi, [ebp + 8]
        mov ecx, [ebp + 12]
        
        jecxz .final
        cld

        .while:
            push ecx

            lodsd
            
            push eax
            push format
            call [printf]
            add esp, 8

            pop ecx
            loop .while

        .final:
        push newline
        call [printf]
        add esp, 4

        pop edi
        pop esi
        pop ebx

        mov esp, ebp
        pop ebp

        ret 8