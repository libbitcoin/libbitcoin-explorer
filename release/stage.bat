@ECHO OFF

COPY   ..\bin\x64\Release\CTP_Nov2013\static\bx.exe  staging\bx-windows-x64-net.exe
COPY ..\bin\Win32\Release\CTP_Nov2013\static\bx.exe  staging\bx-windows-x86-net.exe

PAUSE