@echo off
where gcc >nul 2>nul
if %errorlevel% neq 0 (
    echo GCC is not installed or not in PATH!
    echo Please install MinGW or GCC and add it to your PATH
    echo You can download MinGW from: https://www.mingw-w64.org/downloads/
    pause
    exit /b 1
)

gcc.exe .\resolution.c -o CS2Wrapper.exe
if %errorlevel% equ 0 (
    echo Compilation successful! Created CS2Wrapper.exe
) else (
    echo Compilation failed with error code %errorlevel%
)
pause
