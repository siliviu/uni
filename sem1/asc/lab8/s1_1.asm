bits 32

global start        

extern exit,scanf,printf               
import exit msvcrt.dll    
import scanf msvcrt.dll
import printf msvcrt.dll

segment data use32 class=data
    a resd 1
    b resd 1
    result resq 1
    formatr db "%d %d", 0
    formatw db "%lld", 0

segment code use32 class=code
    start:
        push dword b
        push dword a
        push formatr
        call [scanf]
        add esp, 12

        mov eax, [a]
        mul dword [b]
        mov [result + 4], edx
        mov [result], eax

        push edx
        push eax
        push formatw
        call [printf]
        add esp, 8

        push    dword 0   
        call    [exit]