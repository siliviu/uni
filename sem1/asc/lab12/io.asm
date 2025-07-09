bits 32

global _read, _print
extern _fopen, _fscanf, _printf, _fprintf, _fclose

segment data public data use32
    a dd 0
    mode db "r", 0
    name db "numere.txt", 0
    format db "%d ", 0
    newline db 13,10,0

segment code use32 class=code
    _read:
        push ebp
        mov ebp, esp

        push ebx
        push esi
        push edi

        mov edi, [ebp + 8]
        cld

        push mode
        push name
        call _fopen
        add esp, 8
        mov ebx, eax

        .while:
            push a
            push format
            push ebx
            call _fscanf
            add esp, 12

            cmp eax, 0
            jle .final

            mov esi, a
            movsd

            jmp .while
        
        .final:
            push ebx
            call _fclose
            add esp, 4
            
            mov eax, edi
            
            pop edi
            pop esi
            pop ebx

            mov esp, ebp
            pop ebp

            ret

    _print:
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
            call _printf
            add esp, 8

            pop ecx
            loop .while

        .final:
        push newline
        call _printf
        add esp, 4

        pop edi
        pop esi
        pop ebx

        mov esp, ebp
        pop ebp

        ret