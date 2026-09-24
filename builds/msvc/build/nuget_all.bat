@ECHO OFF
ECHO Downloading libbitcoin vs2026 dependencies from NuGet
CALL nuget.exe install ..\vs2026\bx\packages.config
CALL nuget.exe install ..\vs2026\libbitcoin-explorer\packages.config
CALL nuget.exe install ..\vs2026\libbitcoin-explorer-test\packages.config
