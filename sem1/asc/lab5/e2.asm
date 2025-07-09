bits 32

global start        

extern exit               
import exit msvcrt.dll    

extern printf
import printf msvcrt.dll

segment data use32 class=data
    a dd 24
    b dd 22
    format db "%d", 0xD, 0xA

segment code use32 class=code
    start:
        mov eax, [a]
        cmp eax, [b]    ; eax-b
        ; jb smaller      ; a < b
        ja bigger       ; a > b
    
    ; smaller:
        add eax, 5
        jmp over

    bigger:
        mov ebx, [b]

    over:
        push    dword 0   
        call    [exit]    