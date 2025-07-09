bits 32

global start        

extern exit               
import exit msvcrt.dll    

extern printf
import printf msvcrt.dll

; (a-b)+(c-b-d)+d 
; a byte, b word, c dword, d qword UNSIGNED
segment data use32 class=data
    a db 17
    b dw 9
    c dd 160
    d dq 2560
    r resq 1
    format db "%lld", 0xD, 0xA

segment code use32 class=code
    start:
        mov eax, 0
        mov al, [a]
        sub ax, [b] ; ax = a - b

        mov ebx, [c]
        mov edx, 0
        mov dx, [b]
        sub ebx, edx ; ebx = c-b

        mov edx, 0 ; edx ebx = c-b
        sub ebx, [d]
        sbb edx, [d+4] ; edx ebx = c-b-d

        add ebx, [d]
        adc edx, [d+4] ; edx ebx = (c-b-d)+d

        mov ecx, 0 ; ecx eax = a-b
        add eax, ebx
        adc ecx, edx ; ecx eax = (a-b)+(c-b-d)+d

        mov [r], eax ; r = ecx eax
        mov [r+4], ecx

        push dword [r+4]
        push dword [r]
        push format
        call [printf]

        push    dword 0   
        call    [exit]    