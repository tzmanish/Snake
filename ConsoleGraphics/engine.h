#pragma once
#include<windows.h>

enum block :wchar_t { block0 = 0x0020, block25 = 0x2591, block50 = 0x2592, block75 = 0x2593, block100 = 0x2588 };

HANDLE createConsole(const wchar_t cTitle[]);

bool setFont(const HANDLE &hConsole, short width = 10, short height = 10, WORD color = FOREGROUND_GREEN);

bool fullscreenConsole(const HANDLE &hConsole, const COORD &hCoord);

bool floatingConsole(const HANDLE &hConsole, const COORD &hCoord);