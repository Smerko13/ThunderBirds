#pragma once

#include "Point.h"
#include "Ship.h"
#include "Block.h"
#include <iostream>
#include <cstring>
#include <string>
#include <Windows.h>
#include <conio.h>
#include "general.h"
#include "legend.h"
#include <fstream>
#include <vector>

enum class playingMode{SAVE,LOAD,LOAD_SILENT,REGULAR};

class Board {
private:
protected:
	int ShipsLeft = 2;
	enum class outCome{WIN=1,LOSE=0,NEXT_LEVEL=2,EXIT=3};
	enum class moveOutcomes{STOP=0,MOVE=1,DESTROY_SHIP=2};
	constexpr static size_t WIDTH = 80;
	constexpr static size_t HEIGHT = 25;
	constexpr static size_t NUM_SHIPS = 2;
	char board[HEIGHT][WIDTH + 1] = {' '};
	Ship ships[NUM_SHIPS];
	std::vector<Block> blocks;
	Point exit_pos;
	Legend legend;
public:
	Board();
	void init(const std::string& boardName);
	void show() const {
		for (int i = 0; i < HEIGHT; i++) {
			std::cout << board[i] << std::endl;
		}
	}
	int play(int& livesLeft,std::ofstream& outFile,playingMode mode = playingMode::REGULAR);
	int checkNextPosition(char keyPressed, Ship& ship, char(&board)[25][81],bool silent = false);
	int checkNextPositionForBlock(char keyPressed, Block& block, char(&board)[25][81],bool silent = false);
	void setBoardParameter(const std::string& boardName, char(&board)[25][81]);
	void recordMoveToStepsFile(std::ofstream& outfile, char keyPressed);
};

