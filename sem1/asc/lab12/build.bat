@ECHO OFF 
nasm -fwin32 io.asm
nasm -fwin32 util.asm

FOR /F "tokens=* USEBACKQ" %%v IN (`"C:\Program Files (x86)\Microsoft Visual Studio\Installer\vswhere.exe" -property catalog_productLineVersion`) DO (
CD "C:\Program Files\Microsoft Visual Studio\%%v\Community\VC\Auxiliary\Build\")
CALL vcvars32.bat
CD %~dp0/

cl /Z7 27.c /link io.obj util.obj

DEL 27.obj
DEL util.obj
DEL io.obj
DEL 27.ilk
DEL 27.pdb

ECHO Result:
27.exe