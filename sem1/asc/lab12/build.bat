@ECHO OFF 
nasm -fwin32 io.asm
nasm -fwin32 util.asm

FOR /F "tokens=* USEBACKQ" %%v IN (`powershell.exe -ExecutionPolicy Bypass -Command "Get-ChildItem HKLM:\SOFTWARE\Wow6432Node\Microsoft\Windows\CurrentVersion\Uninstall | foreach { Get-ItemProperty $_.PsPath } | where { $_.DisplayName -like '*Visual Studio*' -and $_.InstallLocation.Length -gt 0 } | sort InstallDate -Descending | foreach { (Join-Path $_.InstallLocation 'Common7\IDE') } | where { Test-Path $_ } | select -First 1"`) DO (
CD /D "%%v\..\..\VC\Auxiliary\Build\")
CALL vcvars32.bat
CD /D %~dp0/

cl /Z7 27.c /link io.obj util.obj

DEL 27.obj util.obj io.obj 27.ilk 27.pdb

ECHO Result:
27.exe