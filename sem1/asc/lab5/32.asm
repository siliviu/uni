; 23, 25
bits 32

global start        

extern exit               
import exit msvcrt.dll    

extern printf
import printf msvcrt.dll

segment data use32 class=data
    s db 1,6,3,1
    l equ $-s
    d times l db 0
    format db "%hhd "

segment code use32 class=code
    start:
        mov ecx, l - 1
        jecxz final
        mov esi, 0

    for:
        mov ax, 0
        mov al, [s+esi]
        div byte [s+esi+1]
        mov [d+esi], al
        inc esi
        loop for 
    
    mov ecx, l - 1
    mov esi, 0

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
        push    dword 0   
        call    [exit]    