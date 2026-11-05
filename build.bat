@echo off
setlocal
cd /d "%~dp0"
where gcc >nul 2>nul
if errorlevel 1 if exist "C:\msys64\ucrt64\bin\gcc.exe" set "PATH=C:\msys64\ucrt64\bin;%PATH%"
if not exist build mkdir build
gcc -c src\charter_gapi.c -Iinclude -O2 -std=c11 -Wall -Wextra -Wpedantic -o build\charter_gapi.o
if errorlevel 1 exit /b 1
ar rcs build\libCharterGAPI.a build\charter_gapi.o
if errorlevel 1 exit /b 1
echo Built build\libCharterGAPI.a
