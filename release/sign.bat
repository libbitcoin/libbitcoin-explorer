@ECHO OFF
SETLOCAL

REM clear WIF key from screen.
CLS

SET SECRET=%1
SET STAGING=staging
SET BX=bx
SET TEMPFILE=batch.tmp
SET ADDRESS=1GpL7EH3QFeG89mZf7dKKssYf4gjrH4mu7
SET SMOKE=54686520736d6f6b65207465737420697320676f6f642e

IF [%SECRET%] == [] (
    ECHO A WIF is required.
    GOTO end
)

"%BX%" wif-to-public %SECRET% | %BX% ec-to-address > %TEMPFILE%
SET /p DERIVED=< %TEMPFILE%
DEL /q %TEMPFILE%

IF NOT %DERIVED% == %ADDRESS% (
    ECHO The WIF is incorrect.
    GOTO end
)

CALL :sign bx-osx-x64-mainnet
CALL :sign bx-osx-x64-testnet
CALL :sign bx-linux-x64-mainnet
CALL :sign bx-linux-x64-testnet
CALL :sign bx-windows-x64-mainnet.exe %SMOKE%
CALL :sign bx-windows-x64-testnet.exe %SMOKE%
CALL :sign bx-windows-x86-mainnet.exe %SMOKE%
CALL :sign bx-windows-x86-testnet.exe %SMOKE%

DIR %STAGING%\bx-*

GOTO end

:sign
SET BINARY=%1
SET DECODE=%2

IF NOT [%DECODE%] == [] (
    "%STAGING%\%BINARY%" fetch-height
    "%STAGING%\%BINARY%" base16-decode %DECODE%
)

ECHO %BINARY%

"%BX%" base16-encode < "%STAGING%\%BINARY%" | "%BX%" sha256 > %TEMPFILE%
SET /p HASH=< %TEMPFILE%
ECHO %HASH%
DEL /q %TEMPFILE%

"%BX%" message-sign %SECRET% %HASH% > %TEMPFILE%
SET /p SIGNATURE=< %TEMPFILE%
ECHO %SIGNATURE%

"%BX%" message-validate %ADDRESS% %SIGNATURE% %HASH%

DEL /q %TEMPFILE%
ECHO.
GOTO end

:end
ENDLOCAL