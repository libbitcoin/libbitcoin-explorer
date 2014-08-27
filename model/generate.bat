@ECHO OFF
REM   Run all code generation scripts
REM   Requires iMatix GSL, from http:\\www.nuget.org\packages\gsl

mkdir ..\src\commands
mkdir ..\include\explorer\commands

gsl -q generate.xml
PAUSE