bits 32

global start        

extern exit               
import exit msvcrt.dll    

extern printf
import printf msvcrt.dll

; A byte string S of length l is given. 
; Obtain the string D of length l-1, such that each element of D is the quotient of two consecutive elements of S, i.e.
; D(i) = S(i) / S(i+1).
segment data use32 class=data
    s db 1,6,3,1
    l equ $-s
    d times l db 0
    format db "%hd "

segment code use32 class=code
    start:
        mov ecx, l - 1
        jecxz final
        mov esi, 0

    for:
        mov ax, 0
        mov al, [s+esi]
        div byte [s+esi+1]
        mov [d+esi], al
        inc esi
        loop for 
    
    mov ecx, l - 1
    mov esi, 0

    print:
        push ecx
        movzx ax, byte [d+esi]
        
        push eax
        push format
        call [printf]
        add esp, 8
        
        inc esi
        pop ecx
        loop print

    final:
        push    dword 0   
        call    [exit]    