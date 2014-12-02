@ECHO OFF
REM   Run all code generation scripts
REM   Requires iMatix GSL, from http:\\www.nuget.org\packages\gsl

if not exist ..\data                                mkdir ..\data
if not exist ..\src\commands                        mkdir ..\src\commands
if not exist ..\include\bitcoin\explorer\commands   mkdir ..\include\bitcoin\explorer\commands

gsl -q generate.xml
PAUSE