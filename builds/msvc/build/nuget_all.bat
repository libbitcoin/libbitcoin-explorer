@ECHO OFF
ECHO Downloading libbitcoin vs2017 dependencies from NuGet
CALL nuget.exe install ..\vs2017\bx\packages.config
CALL nuget.exe install ..\vs2017\libbitcoin-explorer\packages.config
CALL nuget.exe install ..\vs2017\libbitcoin-explorer-test\packages.config
ECHO.
ECHO Downloading libbitcoin vs2015 dependencies from NuGet
CALL nuget.exe install ..\vs2015\bx\packages.config
CALL nuget.exe install ..\vs2015\libbitcoin-explorer\packages.config
CALL nuget.exe install ..\vs2015\libbitcoin-explorer-test\packages.config
ECHO.
ECHO Downloading libbitcoin vs2013 dependencies from NuGet
CALL nuget.exe install ..\vs2013\bx\packages.config
CALL nuget.exe install ..\vs2013\libbitcoin-explorer\packages.config
CALL nuget.exe install ..\vs2013\libbitcoin-explorer-test\packages.config
