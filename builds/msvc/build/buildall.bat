@ECHO OFF
ECHO.
ECHO Downloading sx dependencies from NuGet
CALL nuget.exe install ..\vs2013\libsx\packages.config
CALL nuget.exe install ..\vs2013\sx\packages.config
CALL nuget.exe install ..\vs2013\sx_test\packages.config
ECHO.
CALL buildbase.bat ..\vs2013\sx.sln 12
ECHO.
PAUSE