bits 32

global start        

extern exit               
import exit msvcrt.dll    

extern printf
import printf msvcrt.dll

segment data use32 class=data
    a db 5
    format db "%d", 0xD, 0xA

segment code use32 class=code
    start:  
        mov al, [a]
        add al, 5
        jmp jos
        times 130 nop
    jos: 
        mov eax, 0
        push    dword 0   
        call    [exit]    