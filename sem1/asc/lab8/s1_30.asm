bits 32

global start        

extern exit,scanf,printf               
import exit msvcrt.dll    
import scanf msvcrt.dll
import printf msvcrt.dll

segment data use32 class=data
    x resd 1
    formatr db "%d", 0
    formatw db "%d", 0

segment code use32 class=code
    start:
        mov ebx, (1<<31)-1

        while:
            push x
            push formatr
            call [scanf]
            add esp, 8
            cmp [x], dword 0
            jz end
            cmp [x], ebx
            jge finish
            mov ebx, [x]

            finish:
       
            loop while
        
    end:
        push ebx
        push formatw
        call [printf]
        add esp, 8

        push    dword 0   
        call    [exit]