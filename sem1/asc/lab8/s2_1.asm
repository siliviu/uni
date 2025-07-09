bits 32

global start        

extern exit,fopen,fgetc,fclose,printf               
import exit msvcrt.dll
import fopen msvcrt.dll
import fgetc msvcrt.dll
import fclose msvcrt.dll
import printf msvcrt.dll

segment data use32 class=data
    x resb 1
    name db "input_1.txt", 0
    mode db "r", 0
    formatw db "%d", 0xD, 0xA, 0

segment code use32 class=code
    start:
        mov ebx, 0

        push mode
        push name
        call [fopen]
        add esp, 8
        mov edx, eax

    while:        
        push edx
        call [fgetc]
        pop edx
        cmp eax, -1
        je end
        cmp eax, 'a'
        je good
        cmp eax, 'e'
        je good
        cmp eax, 'i'
        je good
        cmp eax, 'o'
        je good
        cmp eax, 'u'
        je good
        cmp eax, 'A'
        je good
        cmp eax, 'E'
        je good
        cmp eax, 'I'
        je good
        cmp eax, 'O'
        je good
        cmp eax, 'U'
        je good
        jmp finish
        
        good:
            inc ebx
        
        finish:
        loop while
    
    end:
        push edx
        call [fclose]
        add esp, 4

        push ebx
        push formatw
        call [printf]
        add esp, 8

        push    dword 0   
        call    [exit]