#include<iostream>
using namespace std;

#include "engine.h"
#include "snake.h"


int main() {
	HANDLE hConsole = createConsole(L"Snake");
	setFont(hConsole, 12, 12);

	COORD hCoord = {50, 50};
	//floatingConsole(hConsole, {1, 1});
	floatingConsole(hConsole, hCoord);

	wchar_t* screen = new wchar_t[hCoord.X * hCoord.Y];
	SNAKE snake(hCoord);
	COORD food;
	food = snake.placeFood(hCoord);

	DWORD dwBytesWritten = 0;
	while (true) {
		if (snake.body.size() == hCoord.X * hCoord.Y) {	//win
			SetConsoleTextAttribute(hConsole, FOREGROUND_RED);
			for (int i = 0; i < hCoord.X * hCoord.Y; i++) screen[i] = block25;

			swprintf_s(&screen[hCoord.X * (hCoord.Y/2 - 1)], hCoord.X, L"YOU WON!! score: %d    ", snake.body.size()-snake.INIT);
			swprintf_s(&screen[hCoord.X * (hCoord.Y/2)], hCoord.X,     L"Press SPACE to exit...  ");
			WriteConsoleOutputCharacter(hConsole, screen, hCoord.X * hCoord.Y, { 0, 0 }, &dwBytesWritten);
			while (!GetAsyncKeyState(VK_SPACE));
			break;
		}
		if (!snake.move(hCoord, food)) {		//loose
			SetConsoleTextAttribute(hConsole, FOREGROUND_RED);
			for (int i = 0; i < hCoord.X * hCoord.Y; i++) screen[i] = ' ';
			auto it = snake.body.begin();
			while (++it != snake.body.end()) screen[it->Y * hCoord.X + it->X] = '+';
			screen[snake.body.front().Y * hCoord.X + snake.body.front().X] = 'X';

			//stringstream ss;					//////to be implemented
			//ss << snake.body.size() - INIT_LEN;
			swprintf_s(&screen[hCoord.X * (hCoord.Y/2 - 1)], hCoord.X, L"game over! score: %d    ", snake.body.size()-snake.INIT);
			swprintf_s(&screen[hCoord.X * (hCoord.Y/2)], hCoord.X,     L"Press SPACE to exit...  ");
			WriteConsoleOutputCharacter(hConsole, screen, hCoord.X * hCoord.Y, { 0, 0 }, &dwBytesWritten);
			while (!GetAsyncKeyState(VK_SPACE));
			break;
		}

		for (int i = 0; i < hCoord.X * hCoord.Y; i++) screen[i] = ' ';
		short score = snake.body.size() - snake.INIT;
		swprintf_s(&screen[hCoord.X * hCoord.Y - (score ? ((int)log10(score)) + 2 : 2)], score? ((int)log10(score))+2 : 2, L"%d", score);
		screen[food.Y * hCoord.X + food.X] = block50;
		for (const auto& i : snake.body) screen[i.Y * hCoord.X + i.X] = block100;

		WriteConsoleOutputCharacter(hConsole, screen, hCoord.X * hCoord.Y, { 0, 0 }, &dwBytesWritten);
		Sleep(100);
	}

	return 0;
}
