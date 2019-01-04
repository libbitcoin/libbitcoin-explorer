@echo off
REM ###########################################################################
REM  Copyright (c) 2014-2019 libbitcoin developers (see COPYING).
REM
REM  Generate libbitcoin explorer artifacts from XML + GSL.
REM
REM  This executes the iMatix GSL code generator.
REM  See https://github.com/imatix/gsl for details.
REM
REM  Direct GSL download https://www.nuget.org/api/v2/package/gsl/4.1.0.1
REM  Extract gsl.exe from package using NuGet's File > Export
REM ###########################################################################

REM Do everything relative to this file location.
pushd %~dp0

if not exist ..\data                                mkdir ..\data
if not exist ..\src\commands                        mkdir ..\src\commands
if not exist ..\include\bitcoin\explorer\commands   mkdir ..\include\bitcoin\explorer\commands

gsl -q generate.xml

pause
