@echo off
set RAYLIB_BASE=C:\raylib-5.5\build\raylib
g++ src/main.cpp -o app.exe -O2 -std=c++17 -I%RAYLIB_BASE%\include -L%RAYLIB_BASE% -lraylib -lopengl32 -lgdi32 -lwinmm -I src
if %ERRORLEVEL% equ 0 (
    echo Build Successful! Run app.exe
    app.exe
) else (
    echo Build Failed!
    pause
)
