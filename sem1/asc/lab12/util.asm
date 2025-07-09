bits 32

global _construct

segment code use32 class=code
    _construct:
        push ebp
        mov ebp, esp

        push ebx
        push esi
        push edi

        mov esi, [ebp + 8]
        mov ecx, [ebp + 12]
        mov ebx, [ebp + 16]
        mov edi, [ebp + 20]

        jecxz .final
        cld

        .while:
            lodsd
            test eax, 1
            jz .even

            .odd:
                mov [ebx], eax
                add ebx, 4
                jmp .finish
            
            .even:
                mov [edi], eax
                add edi, 4

            .finish:
                loop .while

        .final:
        mov eax, edi
        
        pop edi
        pop esi
        pop ebx

        mov esp, ebp
        pop ebp 
        
        ret