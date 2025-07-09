#ifndef ASMPREPROCESSING_H
#define ASMPREPROCESSING_H

#define BEGIN_PROGRAM "\
bits 32 \n\
global start \n\n\
extern exit \n\
extern exit, printf, scanf \n\
import exit msvcrt.dll \n\
import printf msvcrt.dll \n\
import scanf msvcrt.dll \n\
"

#define INITIAL_DATA_SEGMENT "\
segment data use32 class=data \n\
	read_format db \"%d\", 0 \n\
	write_format db \"%d\", 0 \n\
    swap_variable dd 0 \n\
	aux dd 0 \n\
"

#define DECLARATION_INT_VARIABLE "\
	%s dd %s \n\
"

#define INITIAL_CODE_SEGMENT "\
segment code use32 class=code \n\
start: \n\
"

#define EXIT_CODE "\
push dword 0 \n\
call [exit] \n\
"

#define READ_STMT "\
	push dword %s \n\
	push dword read_format \n\
	call [scanf] \n\
	add esp, 4*2 \n\n\
"

#define WRITE_STMT "\
	push dword [%s] \n\
	push dword write_format \n\
	call [printf] \n\
	add esp, 4*2 \n\
"

#define ASSIGMENT "\
	mov [swap_variable], edx \n\
	mov edx, [%s] \n\
	mov [%s], edx \n\
	mov edx, [swap_variable] \n\n\
"

#define ASSIGMENT_CONSTANT "\
	mov [swap_variable], edx \n\
	mov edx, dword %s \n\
	mov [%s], edx \n\
	mov edx, [swap_variable] \n\n\
"

#define ADDITION_V "\
	mov eax, [%s] \n\
	add eax, [%s] \n\
	mov [%s], eax \n\n\
"

#define ADDITION_C "\
	mov eax, [%s] \n\
	add eax, dword %s \n\
	mov [%s], eax \n\n\
"

#define ADDITION_C_C "\
	mov eax, dword %s \n\
	add eax, dword %s \n\
	mov [%s], eax \n\n\
"

#define ADDITION_C_V "\
	mov eax, dword %s \n\
	add eax, [%s] \n\
	mov [%s], eax \n\n\
"

#define MINUS_V "\
	mov eax, [%s] \n\
	sub eax, [%s] \n\
	mov [%s], eax \n\n\
"

#define MINUS_C "\
	mov eax, [%s] \n\
	sub eax, dword %s \n\
	mov [%s], eax \n\n\
"

#define MINUS_C_C "\
	mov eax, dword %s \n\
	sub eax, dword %s \n\
	mov [%s], eax \n\n\
"

#define MINUS_C_V "\
	mov eax, dword %s \n\
	sub eax, [%s] \n\
	mov [%s], eax \n\n\
"

#define MULTIPLICATION_V "\
	mov eax, [%s] \n\
	mul dword [%s] \n\
	mov [%s], eax \n\n\
"

#define MULTIPLICATION_C "\
	mov eax, [%s] \n\
	mov [aux], dword %s \n\
	mul dword [aux] \n\
	mov [%s], eax \n\n\
"

#define MULTIPLICATION_C_C "\
	mov eax, dword %s \n\
	mov [aux], dword %s \n\
	mul dword [aux] \n\
	mov [%s], eax \n\n\
"

#define MULTIPLICATION_C_V "\
	mov [aux], dword %s \n\
	mov eax, [%s] \n\
	mul dword [aux] \n\
	mov [%s], eax \n\n\
"

#endif