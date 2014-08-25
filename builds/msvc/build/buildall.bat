@ECHO OFF
ECHO.
ECHO Downloading Libbitcoin Explorer dependencies from NuGet
CALL nuget.exe install ..\vs2013\libbitcoin_explorer\packages.config
CALL nuget.exe install ..\vs2013\sx\packages.config
CALL nuget.exe install ..\vs2013\libbitcoin_explorer_test\packages.config
ECHO.
CALL buildbase.bat ..\vs2013\libbitcoin_explorer.sln 12
ECHO.
PAUSE