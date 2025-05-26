#include "boardLoad.h"

//playing the game in replay mode
int BoardLoad::playLoaded(int& livesLeft, std::ifstream& inFile)
{
	std::streamoff pos;
	char keyPressed = 0;
	int seconds;
	inFile >> seconds;
	char direction = 0;
	int shipIndex = 1;
	legend.setLives(livesLeft);
	while (legend.getTimeLeftArg() && legend.getNumOfLivesLeft() > 0)//playing while we have time and lives left
	{
		if (seconds == legend.getSeconds())
		{
			inFile >> keyPressed;
			pos = inFile.tellg();
			inFile >> seconds;
		}
		if (ShipsLeft == 0)//the case we win
			return (int)Board::outCome::WIN;
		legend.printTimer();// prints the legend

		if (_kbhit())
		{
			char tempKey = _getch();
			if (tempKey == 27)//handling the pause menu once the user pressed ESC
			{
				legend.printPause();
			}
		}
		if (!legend.gettimeLeftRaw())//might want to slip this one out
			return (int)Board::outCome::EXIT;
		if (ShipsLeft == 2)//handling active ship controll and display in legend
		{
			if (keyPressed == 'b') {
				shipIndex = 1;
				legend.BigSHipActive();
			}
			else if (keyPressed == 's') {
				shipIndex = 0;
				legend.SmallShipActive();
			}
		}

		for (int i = 0; i < blocks.size(); i++)//first, we make the blocks fall to the ground
		{
			int moveOutcome = checkNextPositionForBlock('x', blocks[i], board);
			blocks[i].eraseBlock(board);
			if (moveOutcome == (int)Board::moveOutcomes::MOVE)
				blocks[i].moveBlock('x', board);
			else if (moveOutcome == (int)Board::moveOutcomes::DESTROY_SHIP)
			{
				inFile.seekg(pos);
				legend.loseLife();
				return (int)Board::outCome::LOSE;
			}
			blocks[i].drawBlock(board);
		}

		//moving the desired ship
		ships[shipIndex].eraseShip(board);
		if (checkNextPosition(keyPressed, ships[shipIndex], board))
		{
			ships[shipIndex].moveShip(keyPressed, board);
		}
		if (ships[shipIndex].getIsInX()) {
			ships[shipIndex].drawShip(' ', board); keyPressed = 'k';
			if (legend.getActive()) {
				shipIndex--;
				legend.SmallShipActive();
			}
			else {
				shipIndex++;
				legend.BigSHipActive();
			}
		}
		else {
			ships[shipIndex].drawShip(ships[shipIndex].getSign(), board);
		}
		Sleep(200);
	}
	legend.loseLife();
	inFile.seekg(pos);
	return (int)Board::outCome::LOSE;
}

//playing the game in silent replay mode
int BoardLoad::playLoadedSilent(int& livesLeft, std::ifstream& inFile, std::vector<std::string> &resultsLoaded)
{
	std::streamoff pos;
	char keyPressed = 0;
	int seconds;
	inFile >> seconds;
	char direction = 0;
	int shipIndex = 1;
	legend.setLives(livesLeft);
	while (legend.getTimeLeftArg() && legend.getNumOfLivesLeft() > 0)//playing while we have time and lives left
	{
		if (seconds == legend.getSeconds())
		{
			inFile >> keyPressed;
			pos = inFile.tellg();
			inFile >> seconds;
		}
		if (ShipsLeft == 0)//the case we win
		{
			resultsLoaded.push_back(std::to_string(legend.getSeconds()));
			resultsLoaded.push_back("WIN");
			return (int)Board::outCome::WIN;
		}

		if (ShipsLeft == 2)//handling active ship controll and display in legend
		{
			if (keyPressed == 'b') {
				shipIndex = 1;
				legend.BigSHipActive();
			}
			else if (keyPressed == 's') {
				shipIndex = 0;
				legend.SmallShipActive();
			}
		}

		for (int i = 0; i < blocks.size(); i++)//first, we make the blocks fall to the ground
		{
			int moveOutcome = checkNextPositionForBlock('x', blocks[i], board, true);
			blocks[i].eraseBlock(board, true);
			if (moveOutcome == (int)Board::moveOutcomes::MOVE)
				blocks[i].moveBlock('x', board);
			else if (moveOutcome == (int)Board::moveOutcomes::DESTROY_SHIP)
			{
				inFile.seekg(pos);
				legend.loseLife();
				resultsLoaded.push_back(std::to_string(legend.getSeconds()));
				resultsLoaded.push_back("LOSE");
				return (int)Board::outCome::LOSE;
			}
			blocks[i].drawBlock(board, true);
		}

		//moving the desired ship
		ships[shipIndex].eraseShip(board, true);
		if (checkNextPosition(keyPressed, ships[shipIndex], board, true))
		{
			ships[shipIndex].moveShip(keyPressed, board);
		}
		if (ships[shipIndex].getIsInX()) {
			ships[shipIndex].drawShip(' ', board, true); keyPressed = 'k';
			if (legend.getActive()) {
				shipIndex--;
				legend.SmallShipActive();
			}
			else {
				shipIndex++;
				legend.BigSHipActive();
			}
		}
		else {
			ships[shipIndex].drawShip(ships[shipIndex].getSign(), board, true);
		}
	}
	legend.loseLife();
	inFile.seekg(pos);
	resultsLoaded.push_back(std::to_string(legend.getSeconds()));
	resultsLoaded.push_back("LOSE");
	return (int)Board::outCome::LOSE;
}