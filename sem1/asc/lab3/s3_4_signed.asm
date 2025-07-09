bits 32

global start        

extern exit               
import exit msvcrt.dll    

extern printf
import printf msvcrt.dll

;(a*2+b/2+e)/(c-d)+x/a
; a-word; b,c,d-byte; e-dword; x-qword SIGNED
segment data use32 class=data
    a dw -17
    b db -9
    c db 40
    d db 15
    e dd -231
    x dq 4124
    twow dw 2
    twob db 2
    r resd 1
    format db "%d", 0xD, 0xA

segment code use32 class=code
    start:
        mov ax, [a]
        imul word [twow] ; dx ax = a*2
        push dx
        push ax
        pop ebx ; ebx = a * 2

        mov al, [b] 
        cbw ; ax = b
        idiv byte [twob] ; al = b/2

        cbw
        cwde ; eax = b/2
        add eax, ebx ; eax = a*2 + b/2

        add eax, [e] ; eax = a*2 + b/2 + e
        push eax

        mov al, [c]
        sub al, [d] ; al = c - d
        cbw
        mov bx, ax ; bx = c - d

        pop ax
        pop dx ; dx ax = a*2+b/2+e

        idiv bx ; ax = (a*2+b/2+e)/(c-d)
        push ax

        mov ax, [a]
        cwde ; eax = a
        mov ebx, eax ; ebx = a

        mov eax, [x]
        mov edx, [x+4] ; edx eax = x

        idiv ebx ; eax = x/a
        mov ebx, eax ; ebx = x/a
        
        pop ax 
        cwde ; eax = (a*2+b/2+e)/(c-d)
        
        add eax, ebx
        mov [r], eax ; r = ans 

        push dword [r]
        push format
        call [printf]

        push    dword 0   
        call    [exit]    