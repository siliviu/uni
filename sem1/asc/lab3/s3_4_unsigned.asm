bits 32

global start        

extern exit               
import exit msvcrt.dll    

extern printf
import printf msvcrt.dll

;(a*2+b/2+e)/(c-d)+x/a
; a-word; b,c,d-byte; e-dword; x-qword UNSIGNED
segment data use32 class=data
    a dw 17
    b db 9
    c db 40
    d db 15
    e dd 231
    x dq 4124
    twow dw 2
    twob db 2
    r resd 1
    format db "%d", 0xD, 0xA

segment code use32 class=code
    start:
        mov ax, [a]
        mul word [twow] ; dx ax = a*2
        push dx
        push ax
        pop ebx ; ebx = a * 2

        mov ax, 0
        mov al, [b] ; ax = b
        div byte [twob] ; al = b/2

        mov edx, 0
        mov dl, al ; edx = b/2
        add ebx, edx ; ebx = a*2 + b/2

        add ebx, [e] ; ebx = a*2 + b/2 + e
        push ebx
        pop ax
        pop dx ; dx ax = (a*2+b/2+e)

        mov bx, 0
        mov bl, [c]
        sub bl, [d] ; bx = c - d

        div bx ; ax = (a*2+b/2+e)/(c-d)
        push ax

        mov eax, [x]
        mov edx, [x+4] ; edx eax = x

        mov ebx, 0
        mov bx, [a] ; ebx = a

        div ebx ; eax = x/a
        
        mov ebx, 0
        pop bx ; ebx = (a*2+b/2+e)/(c-d)
        
        add eax, ebx
        mov [r], eax ; r = ans 

        push dword [r]
        push format
        call [printf]

        push    dword 0   
        call    [exit]    