@echo off
setlocal
cd /d "%~dp0"
where gcc >nul 2>nul
if errorlevel 1 if exist "C:\msys64\ucrt64\bin\gcc.exe" set "PATH=C:\msys64\ucrt64\bin;%PATH%"
call build.bat
if errorlevel 1 exit /b 1
gcc examples\demo.c build\libCharterGAPI.a -Iinclude -O2 -std=c11 -Wall -Wextra -Wpedantic -municode -mwindows -lgdi32 -o build\CharterGapiDemo.exe
if errorlevel 1 exit /b 1
echo Built build\CharterGapiDemo.exe
