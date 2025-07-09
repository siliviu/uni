bits 32

global start        

extern exit               
import exit msvcrt.dll    

extern printf
import printf msvcrt.dll

; a byte b word -> c dword 
; 0 - 7 C = 1;
; 8 - 11 C = 4 - 7 A
; 12 - 19 C = 2 - 9 B
; 20 - 23 C = 0 - 3 A
; 24 - 31 C = 8 - 15 B

segment data use32 class=data
    a db 0x9F;0b1010_1100
    b dw 0xAF9A;0b1100_1101_1101_0011
    c resd 1 ; 0xAFFE 69FF
    format db "%u", 0xD, 0xA

segment code use32 class=code
    start:
        mov eax, 0
        
        or eax, 0b_1111_1111 ; 0 - 7

        mov ebx, [a]
        and ebx, 0b_1111_0000
        shl ebx, 4
        or eax, ebx ; 8 - 11

        mov ebx, [b]
        and ebx, 0b11_1111_1100
        shl ebx, 10
        or eax, ebx ; 12 - 19

        mov ebx, [a]
        and ebx, 0b_1111
        shl ebx, 20
        or eax, ebx ; 20 - 23

        mov ebx, [b]
        and ebx, 0b_1111_1111_0000_0000
        shl ebx, 16
        or eax, ebx ; 24 - 31

        mov [c], eax
        
        push dword [c]
        push format
        call [printf]
        add esp, 8
        
        push    dword 0   
        call    [exit]    