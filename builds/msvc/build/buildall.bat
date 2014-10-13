@ECHO OFF
ECHO.
ECHO Downloading Libbitcoin Explorer dependencies from NuGet
CALL nuget.exe install ..\vs2013\bx\packages.config
CALL nuget.exe install ..\vs2013\libbitcoin-explorer\packages.config
CALL nuget.exe install ..\vs2013\libbitcoin-explorer-test\packages.config
ECHO.
CALL buildbase.bat ..\vs2013\libbitcoin-explorer.sln 12
ECHO.
PAUSE