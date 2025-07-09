bits 32

global start        

extern exit               
import exit msvcrt.dll    

extern printf
import printf msvcrt.dll

; (b+b)-c-(a+d) 
; a byte, b word, c dword, d qword SIGNED
segment data use32 class=data
    a db 17
    b dw 9
    ; b dw 224
    c dd 160
    d dq 2560
    ; d dq 23
    r resq 1
    format db "%lld", 0xD, 0xA

segment code use32 class=code
    start:
        mov ax, [b]
        add ax, [b] ; ax = b + b

        cwde
        sub eax, [c]
        cdq ; edx eax = (b+b)-c
        mov ecx, edx
        mov ebx, eax ; ecx ebx = (b+b)-c

        mov ax, [a]
        cbw
        cwde
        cdq 
        add eax, [d]
        adc edx, [d+4] ; edx eax = a+d

        sub ebx, eax
        sbb ecx, edx ; r = ecx ebx = (b+b)-c-(a+d)

        mov [r], ebx
        mov [r+4], ecx

        push dword [r+4]
        push dword [r]
        push format
        call [printf]

        push    dword 0   
        call    [exit]    