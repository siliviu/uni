bits 32

global start        

extern exit,fopen,scanf,fclose,fprintf               
import exit msvcrt.dll
import fopen msvcrt.dll
import scanf msvcrt.dll
import fclose msvcrt.dll
import fprintf msvcrt.dll

segment data use32 class=data
    x resb 100
    name db "output_30.txt", 0
    mode db "w", 0
    formatr db "%s", 0
    formatw db "%s", 0xD, 0xA, 0

segment code use32 class=code
    start:
        push mode
        push name
        call [fopen]
        add esp, 8
        
        mov ebx, eax

    while:
        push x
        push formatr  
        call [scanf]
        add esp, 8

        cmp byte [x], '$'
        je end

        mov esi, x

        for:
            cmp byte [esi], 0
            je finish
            cmp byte [esi], '9'
            ja continue
            cmp byte [esi], '0'
            jb continue
            jmp print
            continue:
            inc esi
            loop for

        print:
            push dword x
            push formatw
            push ebx
            call [fprintf]
            add esp, 12
        
        finish:
        loop while
    
    end:
        push ebx
        call [fclose]
        add esp, 4

        push    dword 0   
        call    [exit]