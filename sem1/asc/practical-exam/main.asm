bits 32

global start        

extern exit, scanf, fopen, fprintf, fclose, printf               
import exit msvcrt.dll    
import scanf msvcrt.dll
import printf msvcrt.dll
import fopen msvcrt.dll
import fclose msvcrt.dll
import fprintf msvcrt.dll

segment data use32 class=data
    n dd 0
    x dd 0
    one dd -1
    ten dd 10
    filename db "numere2.txt", 0
    mode db "w", 0
    formatn db "n: ", 0
    formats db "Enter numbers: ", 0
    formatread db "%d", 0
    formatp db "%d ", 0

segment code use32 class=code
    start:
        push mode
        push filename
        call [fopen]
        add esp, 8
        mov ebx, eax

        push formatn
        call [printf]
        add esp, 4
        push n
        push formatread
        call [scanf]
        add esp, 8

        push formats
        call [printf]
        add esp, 4

        while:
            push x
            push formatread
            call [scanf]
            add esp, 8
            cmp eax, 0
            jle finish
    
            test dword [x], 1
            jz continue

            mov eax, [x]
            cmp eax, 0
            jge ignore
            imul eax, [one]

            ignore:
            xor edx, edx
            div dword [ten]
            xor edx, edx
            div dword [ten]
            cmp edx, [n]
            jne continue
            
            push dword [x]
            push formatp
            push ebx
            call [fprintf]
            add esp, 12

            continue:
            jmp while

    finish:
        push ebx
        call [fclose]
        add esp, 4

        push    dword 0   
        call    [exit]