#pragma once

#include "game.h"
#include "boardLoad.h"

class GameLoad: public Game
{
	BoardLoad boardLoad;
	std::vector<std::string> resultsLoaded;
	std::vector<std::string> resultFiles;
	std::vector<std::string> loadFiles;
	void checkResult();
public:
	void playLoaded();
	void initiateVectorOfLoadFileNames(const char* identity, std::vector<std::string>& vector);
	void playLoadedSilent();
	
};

