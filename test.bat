@echo off
setlocal
cd /d "%~dp0"
where gcc >nul 2>nul
if errorlevel 1 if exist "C:\msys64\ucrt64\bin\gcc.exe" set "PATH=C:\msys64\ucrt64\bin;%PATH%"
call build.bat
if errorlevel 1 exit /b 1
gcc tests\smoke.c build\libCharterGAPI.a -Iinclude -O2 -std=c11 -Wall -Wextra -Wpedantic -lgdi32 -o build\CharterGapiSmoke.exe
if errorlevel 1 exit /b 1
build\CharterGapiSmoke.exe
