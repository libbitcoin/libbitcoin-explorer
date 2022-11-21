@ECHO OFF
ECHO Downloading libbitcoin vs2022 dependencies from NuGet
CALL nuget.exe install ..\vs2022\bx\packages.config
CALL nuget.exe install ..\vs2022\libbitcoin-explorer\packages.config
CALL nuget.exe install ..\vs2022\libbitcoin-explorer-test\packages.config
ECHO.
ECHO Downloading libbitcoin vs2019 dependencies from NuGet
CALL nuget.exe install ..\vs2019\bx\packages.config
CALL nuget.exe install ..\vs2019\libbitcoin-explorer\packages.config
CALL nuget.exe install ..\vs2019\libbitcoin-explorer-test\packages.config
ECHO.
ECHO Downloading libbitcoin vs2017 dependencies from NuGet
CALL nuget.exe install ..\vs2017\bx\packages.config
CALL nuget.exe install ..\vs2017\libbitcoin-explorer\packages.config
CALL nuget.exe install ..\vs2017\libbitcoin-explorer-test\packages.config