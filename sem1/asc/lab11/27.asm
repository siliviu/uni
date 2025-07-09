bits 32

global start        

extern exit, read, print, construct
import exit msvcrt.dll    


segment data use32 class=data
    four dw 4
    s resd 100
    lens dd 0
    n resd 100
    lenn dd 0
    p resd 100
    lenp dd 0


segment code use32 class=code
    start:
        ; read s
        push s
        call read

        ; calc length of s
        sub eax, s
        mov dx, 0
        div word [four]
        mov [lens], eax

        ; construct p and n
        push p
        push n
        push dword [lens]
        push s
        call construct
        
        ; calc length of p and n
        sub eax, p
        mov dx, 0
        div word [four]
        mov [lenp], eax
        mov ebx, [lens]
        sub ebx, eax
        mov [lenn], ebx

        ; print p
        push dword [lenp]
        push p
        call print

        ; print n
        push dword [lenn]
        push n
        call print

        push dword 0   
        call [exit]