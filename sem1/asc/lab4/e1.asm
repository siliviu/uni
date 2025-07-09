bits 32

global start        

extern exit               
import exit msvcrt.dll    

extern printf
import printf msvcrt.dll

; (a*d+e)/[c+h/(c-b)]
; a,b,c,d-byte, e,f,g,h-word
segment data use32 class=data
    a db 1
    b db 2
    c db 3
    d db 4
    e dw 12
    f dw 13
    g dw 14
    h dw 15
    r resb 1
    format db "%hd", 0xD, 0xA

segment code use32 class=code
    start:
        mov al, [a]
        mul byte [d] ; ax = a * d

        add ax, [e] ; cx = ax = a * d + e
        mov cx, ax

        mov bl, [c]
        sub bl, [b] ; bl = c-b

        mov ax, [h] 
        div bl ; al = h/(c-b)

        add al, [c] ; bl = al =c+h/(c-b)
        mov bl, al 
        
        mov ax, cx ; ax = a*d+e

        div bl ; r = al = (a*d+e)/(c+h/(c-b))
        mov [r], al

        mov bx, 0
        mov bl, [r]
        push word bx
        push format
        call [printf]

        push    dword 0   
        call    [exit]    