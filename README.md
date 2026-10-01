# Classic Snake Game in C 

A lightweight, terminal-based Snake Game built in C for Windows console without external graphics libraries.

## Features
- Arrow keys & WASD control support
- Non-flickering, smooth frame rendering using Windows Console API (`SetConsoleCursorPosition`)
- Auto-growing tail logic & score tracking
- Optimized for laptop terminals (16:9 aspect ratio grid)

## How to Compile & Run
Make sure you have GCC (MinGW / MSYS2) installed on Windows:

--Commands To Run Game----
gcc main.c -o snake.exe
.\snake.exe
