#pragma once

#include "Point.h"
#include "general.h"
#include <iostream>

class Board;

class Ship {
	constexpr static size_t MAX_SHIP_SIZE = 4;
	char sign;
	bool isInX = false;
	Point pos[MAX_SHIP_SIZE];
	size_t size = 0;
public:
	void setSign(char sign) {
		this->sign = sign;
	}
	char getSign() const {
		return this->sign;
	}
	void setIsInX(bool isInX) {
		this->isInX = isInX;
	}
	bool getIsInX() const {
		return this->isInX;
	}
	void addPoint(int x, int y) {
		pos[size++].set(x, y);
	}
	size_t getSize() const {
		return size;
	}
	Point getPos(size_t i) const {
		return pos[i];
	}
	void moveShip(int direction, char(&board)[25][81]);
	void drawShip(char shipType, char(&board)[25][81], bool silent = false);
	void eraseShip(char(&board)[25][81],bool silent = false);
	void moveShipToWinningPosition(char(&board)[25][81]);
};