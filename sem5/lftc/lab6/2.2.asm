bits 32 
global start 

extern exit 
extern exit, printf, scanf 
import exit msvcrt.dll 
import printf msvcrt.dll 
import scanf msvcrt.dll 

segment data use32 class=data 
	read_format db "%d", 0 
	write_format db "%d", 0 
    swap_variable dd 0 
	aux dd 0 

	x dd 0 
	y dd 0 
	temp0 dd 0 
	temp1 dd 0 
	temp2 dd 0 

segment code use32 class=code 
start: 

	push dword x 
	push dword read_format 
	call [scanf] 
	add esp, 4*2 

	mov [aux], dword 2 
	mov eax, [x] 
	mul dword [aux] 
	mov [temp0], eax 

	mov eax, dword 3 
	add eax, [temp0] 
	mov [temp1], eax 

	mov eax, [temp1] 
	add eax, dword 3 
	mov [temp2], eax 

	mov [swap_variable], edx 
	mov edx, [temp2] 
	mov [y], edx 
	mov edx, [swap_variable] 

	push dword [y] 
	push dword write_format 
	call [printf] 
	add esp, 4*2 

push dword 0 
call [exit] 

