@ECHO OFF
REM   Run all code generation scripts
REM   Requires iMatix GSL, from http:\\www.nuget.org\packages\gsl

mkdir ..\include\sx\command

gsl -q generate.xml
PAUSE