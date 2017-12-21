REM ###########################################################################
REM #  Copyright (c) 2014-2015 libbitcoin-explorer developers (see COPYING).
REM #
REM #         GENERATED SOURCE CODE, DO NOT EDIT EXCEPT EXPERIMENTALLY
REM #
REM ###########################################################################
@echo off
SETLOCAL ENABLEEXTENSIONS
SET "parent=%~dp0"
SET "path_base=%~1"
SET "nuget_pkg_path=%~1\..\nuget"
SET "msbuild_args=/verbosity:minimal /p:Platform=%~2 /p:Configuration=%~3"
SET "proj_version=%~4"
SET "msbuild_exe=msbuild"
IF EXIST "%~5" SET "msbuild_exe=%~5"

call :pending "Build initialized..."
IF NOT EXIST "%nuget_pkg_path%" (
  call mkdir "%nuget_pkg_path%"
  IF %ERRORLEVEL% NEQ 0 (
    call :failure "mkdir %nuget_pkg_path% failed."
    exit /b 1
  )
)

call :init libbitcoin libbitcoin master
IF %ERRORLEVEL% NEQ 0 (
  call :failure "Initializing repository libbitcoin libbitcoin master failed."
  exit /b 1
)
call :init libbitcoin libbitcoin-protocol master
IF %ERRORLEVEL% NEQ 0 (
  call :failure "Initializing repository libbitcoin libbitcoin-protocol master failed."
  exit /b 1
)
call :init libbitcoin libbitcoin-client master
IF %ERRORLEVEL% NEQ 0 (
  call :failure "Initializing repository libbitcoin libbitcoin-client master failed."
  exit /b 1
)
call :init libbitcoin libbitcoin-network master
IF %ERRORLEVEL% NEQ 0 (
  call :failure "Initializing repository libbitcoin libbitcoin-network master failed."
  exit /b 1
)
call :bld_repo libbitcoin-explorer
IF %ERRORLEVEL% NEQ 0 (
  call :failure "Building libbitcoin-explorer failed."
  exit /b 1
)

call :success "Build complete."
exit /b 0



:init
call :pending "Initializing repository %~1/%~2/%~3..."
IF NOT EXIST "%path_base%\%~2" (
  call git clone -q --branch=%~3 https://github.com/%~1/%~2 "%path_base%\%~2"
  IF %ERRORLEVEL% NEQ 0 (
    call :failure "git clone %~1/%~2 failed."
    exit /b 1
  )
) ELSE (
  call :success "%path_base%\%~2 exists, assuming valid clone."
)

call :bld_proj %~2
IF %ERRORLEVEL% NEQ 0 (
  call :failure "Building project %~2 failed."
  exit /b 1
)
call :success "Initialization of %~1/%~2/%~3 complete."
exit /b 0

:bld_repo
call :pending "Building respository %~1..."
call :depends "%~1"
IF %ERRORLEVEL% NEQ 0 (
  call :failure "Initializing dependencies %~1 failed."
  exit /b 1
)
call cd /d "%path_base%\%~1\builds\msvc\%proj_version%"
call "%msbuild_exe%" %msbuild_args% %~1.sln
IF %ERRORLEVEL% NEQ 0 (
  call :failure "%msbuild_exe% %msbuild_args% %~1.sln failed."
  exit /b 1
)
call :success "Building repository %~1 execution complete."
call cd /d "%path_base%"
exit /b 0

:bld_proj
call :pending "Building respository project %~1..."
call :depends %~1
IF %ERRORLEVEL% NEQ 0 (
  call :failure "Initializing dependencies %~1 failed."
  exit /b 1
)
call cd /d "%path_base%\%~1\builds\msvc\%proj_version%"
call "%msbuild_exe%" %msbuild_args% /target:%~1:Rebuild %~1.sln
IF %ERRORLEVEL% NEQ 0 (
  call :failure "%msbuild_exe% %msbuild_args% /target:%~1:Rebuild %~1.sln"
  exit /b 1
)
call :success "Building repository project %~1 execution complete."
call cd /d "%path_base%"
exit /b 0

:depends
call :pending "nuget restoring dependencies for %~1..."
call nuget restore "%path_base%\%~1\builds\msvc\%proj_version%\%~1.sln" -Outputdir "%nuget_pkg_path%"
IF %ERRORLEVEL% NEQ 0 (
  call :failure "nuget restore failed."
  exit /b 1
)
call :success "nuget restoration for %~1 complete."
exit /b 0

:pending
echo [93m%~1[0m
exit /b 0

:success
echo [92m%~1[0m
exit /b 0

:failure
echo [91m%~1[0m
exit /b 0
