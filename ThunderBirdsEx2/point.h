#pragma once

class Point {
	int x, y;
public:
	void set(int x1, int y1) {
		x = x1;
		y = y1;
	}
	int getX() const {
		return x;
	}
	int getY() const {
		return y;
	}
};