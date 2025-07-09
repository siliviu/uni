@ECHO OFF
nasm -fobj 27.asm
nasm -fobj util.asm
nasm -fobj io.asm

alink 27.obj util.obj io.obj -oPE -subsys console -entry start

DEL 27.obj util.obj io.obj

ECHO Result:
27.exe