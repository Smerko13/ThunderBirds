#pragma once

#include "board.h"

class BoardLoad:public Board
{
private:
	static std::vector<std::string>result;
public:
	int playLoaded(int& livesLeft, std::ifstream& inFile);
	int playLoadedSilent(int& livesLeft, std::ifstream& inFile, std::vector<std::string> &resultsLoaded);
};

