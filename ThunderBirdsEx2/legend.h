#pragma once

#include <iostream>
#include <Windows.h>
#include "general.h"
#include <conio.h>
#include "point.h"

class Legend
{
	Point pos;
	int seconds = 500;
	enum class numOfDigits{One=9,Two=100};
	static constexpr int ZERO = 0;
	bool timeLeft = true;
	bool activeShip = true;
	static int numOfLivesLeft;

public:
	bool getTimeLeftArg();
	bool gettimeLeftRaw() const { return timeLeft; }
	void setTimeLeftArg(bool val) { timeLeft = val;}
	void printTimer() const;
	void BigSHipActive() { activeShip = true; }
	void SmallShipActive() { activeShip = false; }
	int getNumOfLivesLeft() const { return numOfLivesLeft; }
	void loseLife() { numOfLivesLeft--; }
	void printPause();
	bool getActive() const { return activeShip; }
	void setPos(int x, int y) { pos.set(x, y); }
	void resetTime() { seconds = 300;}
	void resetLives() { numOfLivesLeft = 3; }
	void setLives(int num) { numOfLivesLeft = num; }
	int getSeconds() const { return seconds; }
};

