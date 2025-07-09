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

	x dd 10 
	temp0 dd 0 
	temp1 dd 0 
	temp2 dd 0 
	temp3 dd 0 
	temp4 dd 0 
	temp5 dd 0 
	temp6 dd 0 
	y dd 0 

segment code use32 class=code 
start: 

	mov [swap_variable], edx 
	mov edx, dword 10 
	mov [x], edx 
	mov edx, [swap_variable] 

	mov [aux], dword 5 
	mov eax, [x] 
	mul dword [aux] 
	mov [temp0], eax 

	mov eax, dword 3 
	add eax, [temp0] 
	mov [temp1], eax 

	mov eax, dword 4 
	mov [aux], dword 5 
	mul dword [aux] 
	mov [temp2], eax 

	mov eax, [temp1] 
	sub eax, [temp2] 
	mov [temp3], eax 

	mov eax, dword 6 
	mov [aux], dword 2 
	mul dword [aux] 
	mov [temp4], eax 

	mov eax, [temp3] 
	add eax, [temp4] 
	mov [temp5], eax 

	mov eax, [temp5] 
	add eax, [x] 
	mov [temp6], eax 

	mov [swap_variable], edx 
	mov edx, [temp6] 
	mov [y], edx 
	mov edx, [swap_variable] 

	push dword [y] 
	push dword write_format 
	call [printf] 
	add esp, 4*2 

push dword 0 
call [exit] 

