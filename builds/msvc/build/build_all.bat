@ECHO OFF
CALL nuget_all.bat
ECHO.
CALL build_base.bat vs2026 libbitcoin-explorer "Microsoft Visual Studio\18\Community\VC\Auxiliary\Build"
PAUSE
