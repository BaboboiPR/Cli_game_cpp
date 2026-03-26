#pragma once
#ifdef _WIN32
#include <windows.h>
#include <string>
#include <iostream>
class WinApi {
public:
    static void enable_ansi_colors()
    {
        HANDLE hOut = GetStdHandle(STD_OUTPUT_HANDLE);
        DWORD dwMode = 0;
        if (GetConsoleMode(hOut, &dwMode)) {
            dwMode |= ENABLE_VIRTUAL_TERMINAL_PROCESSING;
            SetConsoleMode(hOut, dwMode);
        }
    }

    static void fastPrint(const std::string& s) {
        DWORD written;
        HANDLE h = GetStdHandle(STD_OUTPUT_HANDLE);
        WriteConsoleA(h, s.c_str(), s.size(), &written, nullptr);
    }

    static void clearScreen() {
        HANDLE h = GetStdHandle(STD_OUTPUT_HANDLE);

        CONSOLE_SCREEN_BUFFER_INFO csbi;
        GetConsoleScreenBufferInfo(h, &csbi);

        DWORD cellCount = csbi.dwSize.X * csbi.dwSize.Y;
        DWORD count;

        COORD home = {0, 0};

        // fill entire buffer with spaces
        FillConsoleOutputCharacter(h, ' ', cellCount, home, &count);

        // reset all attributes (color, bold, etc)
        FillConsoleOutputAttribute(h, csbi.wAttributes, cellCount, home, &count);

            // put cursor at top-left
        SetConsoleCursorPosition(h, home);
        std::cout << "\033[2J";
    }

    void Input(char& line) {
        if (GetAsyncKeyState('Q') & 0x8000) line='q';
        if (GetAsyncKeyState('W') & 0x8000) line='w';
        if (GetAsyncKeyState('E') & 0x8000) line='e';
        if (GetAsyncKeyState('R') & 0x8000) line='r';
        if (GetAsyncKeyState('T') & 0x8000) line='t';
        if (GetAsyncKeyState('Y') & 0x8000) line='y';
        if (GetAsyncKeyState('U') & 0x8000) line='u';
        if (GetAsyncKeyState('I') & 0x8000) line='i';
        if (GetAsyncKeyState('O') & 0x8000) line='o';
        if (GetAsyncKeyState('P') & 0x8000) line='p';
        if (GetAsyncKeyState('A') & 0x8000) line='a';
        if (GetAsyncKeyState('S') & 0x8000) line='s';
        if (GetAsyncKeyState('D') & 0x8000) line='d';
        if (GetAsyncKeyState('F') & 0x8000) line='f';
        if (GetAsyncKeyState('G') & 0x8000) line='g';
        if (GetAsyncKeyState('H') & 0x8000) line='h';
        if (GetAsyncKeyState('J') & 0x8000) line='j';
        if (GetAsyncKeyState('K') & 0x8000) line='k';
        if (GetAsyncKeyState('L') & 0x8000) line='l';
        if (GetAsyncKeyState('Z') & 0x8000) line='z';
        if (GetAsyncKeyState('X') & 0x8000) line='x';
        if (GetAsyncKeyState('C') & 0x8000) line='c';
        if (GetAsyncKeyState('V') & 0x8000) line='v';
        if (GetAsyncKeyState('B') & 0x8000) line='b';
        if (GetAsyncKeyState('N') & 0x8000) line='n';
        if (GetAsyncKeyState('M') & 0x8000) line='m';
        if (GetAsyncKeyState(VK_SPACE) & 0x8000) line=' ';
        }
    };
#endif