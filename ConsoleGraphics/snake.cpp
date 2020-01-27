#include "snake.h"

SNAKE::SNAKE(const COORD &hCoord) {
	INIT = 3;
	for (int i = 0; i < INIT; i++) body.push_back({ hCoord.X / 2, hCoord.Y / 2 });
	dir = RIGHT;
}

bool SNAKE::isPositionAvailable(const COORD &pos) {
	for (const auto& i : body) if (i.X == pos.X && i.Y == pos.Y) return false;
	return true;
}

bool SNAKE::move(const COORD &hCoord, COORD &food) {
	if ((GetAsyncKeyState(VK_UP) & 0x8000) | (GetAsyncKeyState((unsigned short)'W') & 0x8000) && dir != DOWN) dir = UP;
	else if ((GetAsyncKeyState(VK_DOWN) & 0x8000) | (GetAsyncKeyState((unsigned short)'S') & 0x8000) && dir != UP) dir = DOWN;
	else if ((GetAsyncKeyState(VK_LEFT) & 0x8000) | (GetAsyncKeyState((unsigned short)'A') & 0x8000) && dir != RIGHT) dir = LEFT;
	else if ((GetAsyncKeyState(VK_RIGHT) & 0x8000) | (GetAsyncKeyState((unsigned short)'D') & 0x8000) && dir != LEFT) dir = RIGHT;

	body.push_front({
		(hCoord.X + body.front().X + dir / 10) % hCoord.X,
		(hCoord.Y + body.front().Y + dir % 10) % hCoord.Y
		});
	body.pop_back();

	if (body.front().X == food.X && body.front().Y == food.Y) {
		body.push_back(body.back());
		food = placeFood(hCoord);
	}
	else {
		auto it = body.begin();
		while (++it != body.end()) if (body.front().X == it->X && body.front().Y == it->Y) return false;
	}

	return true;
}

COORD SNAKE::placeFood(const COORD &hCoord) {
	COORD pos;
	do {
		pos.X = rand() % hCoord.X;
		pos.Y = rand() % hCoord.Y;
	} while (!isPositionAvailable(pos));
	return pos;
}