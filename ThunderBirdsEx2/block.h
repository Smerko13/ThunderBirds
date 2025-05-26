#pragma once

#include "Point.h"
#include <iostream>
#include "general.h"

class Board;

class Block {
	constexpr static size_t MAX_BlOCK_SIZE = 6;
	Point pos[MAX_BlOCK_SIZE];
	size_t size = 0;
	char type;
public:
	void addPoint(int x, int y) {
		pos[size++].set(x, y);
	}
	size_t getSize() const {
		return size;
	}
	Point getPos(size_t i) const {
		return pos[i];
	}
	void setType(char type) {
		this->type = type;
	}
	char getType() const{
		return this->type;
	}
	void moveBlock(char direction, char(&board)[25][81]);
	void drawBlock(char(&board)[25][81],bool silent = false);
	void eraseBlock(char(&board)[25][81],bool silent = false);
};