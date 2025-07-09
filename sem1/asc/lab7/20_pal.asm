bits 32

global start        

extern exit               
import exit msvcrt.dll    

extern printf
import printf msvcrt.dll

segment data use32 class=data
    s db 'Ana are un cojoc a'
    len equ $-s
    max_word equ 50
    cur resb max_word
    format db "Palindrom: %s", 13, 10

segment code use32 class=code
    start:
        mov ecx, len
        jecxz final
        cld
        mov esi, s
    
    next:
        mov ebx, 0
        mov edi, cur

    for:
        lodsb
    
        cmp al, ' '
        je space
    
        stosb
        inc ebx
        loop for
    
    space:
        push ecx
        push esi

        mov ecx, ebx
        cld
        mov esi, cur
        mov edi, cur
        add edi, ebx
        dec edi    

        check:
            lodsb
            std
            scasb
            cld
            jnz notapal
            loop check
        
        mov [cur+ebx], byte 0
        push cur
        push format
        call [printf]
        add esp, 8

        notapal:
            pop esi 
            pop ecx
            jecxz final
            dec ecx
            jnz next

    final:
        push    dword 0   
        call    [exit]    