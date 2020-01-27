#include "engine.h"

HANDLE createConsole(const wchar_t cTitle[]) {
	HANDLE hConsole = CreateConsoleScreenBuffer(GENERIC_READ | GENERIC_WRITE, 0, NULL, CONSOLE_TEXTMODE_BUFFER, NULL);
	SetConsoleActiveScreenBuffer(hConsole);

	SetConsoleTitle(cTitle);

	CONSOLE_CURSOR_INFO cInfo;
	GetConsoleCursorInfo(hConsole, &cInfo);
	cInfo.bVisible = false;
	SetConsoleCursorInfo(hConsole, &cInfo);

	return hConsole;
}

bool setFont(const HANDLE &hConsole, short width, short height, WORD color) {
	CONSOLE_FONT_INFOEX cfi;
	GetCurrentConsoleFontEx(hConsole, false, &cfi);
	cfi.cbSize = sizeof(cfi);
	cfi.nFont = 0;
	cfi.dwFontSize.X = width;                   // Width of each character in the font
	cfi.dwFontSize.Y = height;                   // Height
	cfi.FontFamily = FF_DONTCARE;
	cfi.FontWeight = FW_NORMAL;
	wcscpy_s(cfi.FaceName, L"Ariel");
	SetConsoleTextAttribute(hConsole, color);  //color
	SetCurrentConsoleFontEx(hConsole, false, &cfi);

	return true;
}

bool fullscreenConsole(const HANDLE &hConsole, const COORD &hCoord) {
	COORD hMaxCoord;
	SetConsoleDisplayMode(hConsole, 1, &hMaxCoord);
	CONSOLE_SCREEN_BUFFER_INFO hBufferInfo;
	GetConsoleScreenBufferInfo(hConsole, &hBufferInfo);
	hMaxCoord = hBufferInfo.dwMaximumWindowSize;

	SMALL_RECT hArea;
	hArea.Left = (hMaxCoord.X - hCoord.X) / 2;
	hArea.Top = (hMaxCoord.Y - hCoord.Y) / 2;
	hArea.Right = hArea.Left + hCoord.X - 1;
	hArea.Bottom = hArea.Top + hCoord.Y - 1;
	if (hArea.Top < 0 || hArea.Left < 0) return false;		//Exception

	wchar_t* screen = new wchar_t[hMaxCoord.X * hMaxCoord.Y];
	for (int i = 0; i < hMaxCoord.X * hMaxCoord.Y; i++) {
		if (i / hMaxCoord.X < hArea.Top || i / hMaxCoord.X > hArea.Bottom || i % hMaxCoord.X < hArea.Left || i % hMaxCoord.X > hArea.Right)
			screen[i] = '-';
		else screen[i] = block(i % 5);
	}
	DWORD dwBytesWritten = 0;
	WriteConsoleOutputCharacter(hConsole, screen, hMaxCoord.X * hMaxCoord.Y, { 0, 0 }, &dwBytesWritten);

	return true;
}

bool floatingConsole(const HANDLE &hConsole, const COORD &hCoord) {
	//Centre
	MoveWindow(GetConsoleWindow(), 0, 0, 1, 1, TRUE);

	SMALL_RECT hArea = { 0, 0, hCoord.X - 1, hCoord.Y - 1 };
	SetConsoleScreenBufferSize(hConsole, hCoord);            // Set Buffer Size 
	SetConsoleWindowInfo(hConsole, TRUE, &hArea);            // Set Window Size 

	return true;
}