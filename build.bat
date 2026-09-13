@echo off
title Mod Build Script

:: Cmake build
cmake -B build

:: Start compiling
if %ERRORLEVEL% EQU 0 (
    echo.
    echo --- Compiling... ---
    cmake --build build --config Release
)

:: Prevent the window from closing.
echo.
pause