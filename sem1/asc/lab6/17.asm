bits 32

global start        

extern exit               
import exit msvcrt.dll    

extern printf
import printf msvcrt.dll

segment data use32 class=data
    ; sir dd 12345678h, 1256ABCDh, 12AB4344h
    sir dd 5,1,3,2,8,2,7,1
    l equ ($-sir)/4
    format db "%x ", 0

segment code use32 class=code
    start:
        mov ecx, l
        jecxz final
        mov esi, sir
        cld

    for:
        mov edx, ecx
        sub edx, 1
        push ecx
        lodsw ; ax = a[i]

        mov ecx, edx
        jecxz continue

        mov edx, esi
        add edx, 2
        push esi
        mov esi, edx ; esi = j = i + 1

        for2:
            mov bx, ax ; bx = a[i]
            lodsw ; ax = a[j] 
            cmp bx, ax
            mov dx, bx ; dx = a[i]

            jae next ; -> a[j] > a[i] -> swap a[i] and a[j]
            mov dx, ax ; dx = a[j]
            mov ax, bx ; ax = a[i]
            mov edi, esi 
            sub edi, 2 ; edi = j
            stosw ; a'[j] = a[i] 1/2

            mov ax, dx ; ax = a[j]

            pop ebx
            mov edi, ebx ; edi = i
            sub edi, 2
            push ebx

            stosw ; a'[i] = a[j] 2/2
            
            next:
            lodsw
            mov ax, dx ; ax = max(a[i],a[j])
            loop for2
        
        pop esi ; esi = i

        continue:
        lodsw
        pop ecx
        loop for 

    final:
        mov ecx, l
        mov esi, sir

        print:
            push ecx
            
            lodsd
            push eax
            push format
            call [printf]
            add esp, 8

            pop ecx
            loop print
            
        push    dword 0   
        call    [exit]    