#include "board.h"
#include <cctype>

//C'tor to help us fill in a missing board in case one was provided
Board::Board()
{
	for (int i = 0; i < HEIGHT; i++) {
		for (int j = 0; j < WIDTH; j++) {
			board[i][j] = 'W';
		}
	}
}

//initiating the data for the board provided
void Board::init(const std::string& boardName)
{
	blocks.clear();
	setBoardParameter(boardName, board);
	ships[0].setSign('@');
	ships[1].setSign('#');
	for (int i = 0; i < HEIGHT; i++) {
		for (int j = 0; j < WIDTH; j++) {
			if (board[i][j] == '@') {
				ships[0].addPoint(j, i);
			}
			else if (board[i][j] == '#') {
				ships[1].addPoint(j, i);
			}
			else if (board[i][j] >= 'a' && board[i][j] <= 'z') {
				Block temp;
				bool flag = true;
				for (Block& b : blocks) {
					if (b.getType() == board[i][j])
					{
						b.addPoint(j, i);
						flag = false;
					}
				}
				if (flag)
				{
					blocks.push_back(temp);
					blocks[blocks.size() - 1].addPoint(j, i);
					blocks[blocks.size() - 1].setType(board[i][j]);
				}
			}
			else if (board[i][j] == 'X') {
				exit_pos.set(j, i);
			}
			else if (board[i][j] == '&') {
				legend.setPos(j, i);
			}
		}
	}
}
//playing regulary or in save mode
int Board::play(int& livesLeft, std::ofstream& outFile, playingMode mode)
{
	char keyPressed = 0;
	char direction = 0;
	int shipIndex = 1;
	legend.setLives(livesLeft);
	while (legend.getTimeLeftArg() && legend.getNumOfLivesLeft() > 0)//playing while we have time and lives left
	{
		if (ShipsLeft == 0)//the case we win
		{
			return (int)Board::outCome::WIN;
		}
		legend.printTimer();// prints the legend
		if (_kbhit())//taking care of user input
		{
			keyPressed = tolower(_getch());
			if (mode == playingMode::SAVE) { recordMoveToStepsFile(outFile, keyPressed); }
			if (keyPressed == 27)//handling the pause menu once the user pressed ESC
			{
				legend.printPause();
			}
			if (!legend.gettimeLeftRaw())
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
		}

		for (int i = 0; i < blocks.size(); i++)//first, we make the blocks fall to the ground
		{
			int moveOutcome = checkNextPositionForBlock('x', blocks[i], board);
			blocks[i].eraseBlock(board);
			if (moveOutcome==(int)Board::moveOutcomes::MOVE)
				blocks[i].moveBlock('x', board);
			else if (moveOutcome == (int)Board::moveOutcomes::DESTROY_SHIP)
			{
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
	return (int)Board::outCome::LOSE;
}

//checking the next position, intended for ship movment
int Board::checkNextPosition(char keyPressed, Ship& ship, char(&board)[25][81],bool silent)
{
	int l, j;
	char boardCh;;
	switch (keyPressed)
	{
	case 'w':
		l = -1;
		j = 0;
		break;
	case 'd':
		l = 0; j = 1;
		break;
	case 'x':
		l = 1; j = 0;
		break;
	case 'a':
		l = 0; j = -1;
		break;
	default:

		return false;
	}
	for (int i = 0; i < ship.getSize(); i++)
	{
		int nextX = ship.getPos(i).getY() + l;
		int nextY = ship.getPos(i).getX() + j;

		boardCh = board[nextX][nextY];
		if (boardCh == 'W'|| boardCh == '@'|| boardCh == '#')
			return (int)Board::moveOutcomes::STOP;
		else if (boardCh == 'X')
		{
			ship.moveShipToWinningPosition(board);
			ShipsLeft--;
			keyPressed = 'z';
			return (int)Board::moveOutcomes::STOP;
		}
		else if (boardCh >= 'a' && boardCh <= 'z')
		{
			int blockIndex;
			int counter = 0;
			for (const Block& b : blocks)
			{
				if (b.getType() == boardCh)
					blockIndex = counter;
				counter++;
			}

			if (legend.getActive() && blocks[blockIndex].getSize() > ship.getSize() + 2)
				return (int)Board::moveOutcomes::STOP;
			else if (!legend.getActive() && blocks[blockIndex].getSize() > ship.getSize()) {
				return (int)Board::moveOutcomes::STOP;
			}
			else
			{
				if (checkNextPositionForBlock(keyPressed, blocks[blockIndex], board))
				{
					blocks[blockIndex].eraseBlock(board,silent);
					blocks[blockIndex].moveBlock(keyPressed, board);
					blocks[blockIndex].drawBlock(board,silent);
					return (int)Board::moveOutcomes::MOVE;
				}
				else
					return (int)Board::moveOutcomes::STOP;
			}
		}
	}
	return (int)Board::moveOutcomes::MOVE;
}

//checking movment for blocks
int Board::checkNextPositionForBlock(char keyPressed, Block& block, char(&board)[25][81],bool silent) {
	char boardCh;
	int l, j;
	switch (keyPressed)
	{
	case 'w':
		l = -1;
		j = 0;
		break;
	case 'd':
		l = 0; j = 1;
		break;
	case 'x':
		l = 1; j = 0;
		break;
	case 'a':
		l = 0; j = -1;
		break;
	default:
		return false;
	}
	for (int i = 0; i < block.getSize(); i++) {
		boardCh = board[block.getPos(i).getY() + l][block.getPos(i).getX() + j];
		if (boardCh == 'W') {
			return (int)Board::moveOutcomes::STOP;
		}
		else if (boardCh == '@' && block.getSize() <= 2) {
			return (int)Board::moveOutcomes::STOP;
		}
		else if (boardCh == '#' && block.getSize() <= 6) {
			return (int)Board::moveOutcomes::STOP;
		}
		else if (boardCh >= 'a' && boardCh <= 'z' && boardCh != block.getType()) {
			return (int)Board::moveOutcomes::STOP;
		}
		else if (boardCh == '@' && block.getSize() >= 3 && keyPressed == 'x') {
			return (int)Board::moveOutcomes::DESTROY_SHIP;
		}
		else if (boardCh == '@' && block.getSize() >= 3 && keyPressed != 'x')
		{
			ships[0].eraseShip(board,silent);
			ships[0].moveShip(keyPressed, board);
			ships[0].drawShip('@', board,silent);
			return (int)Board::moveOutcomes::STOP;
		}
		
	}
	return (int)Board::moveOutcomes::MOVE;
}

//reading a map from a file
void Board::setBoardParameter(const std::string& boardName, char(&board)[25][81])// need to take care of case board ddint open
{
	std::ifstream file(boardName);
	if (!file.is_open())
	{
		std::cout << "Failed to read data from board";
	}

	char ch;
	int row = 0;
	int col = 0;

	while (file.get(ch))
	{
		if (ch == '\n')
		{
			row++;
			col = 0;
			if (row >= HEIGHT)
				break;
		}
		else
		{
			if (col < WIDTH + 1)
				board[row][col] = ch;
			col++;
		}
	}
	file.close();
}

//recording the needed movments for steps file, quite redundant
void Board::recordMoveToStepsFile(std::ofstream& outfile, char keyPressed)
{
	if(keyPressed=='a'|| keyPressed == 'x' || keyPressed == 'd' || keyPressed == 'w' || keyPressed == 's' || keyPressed == 's' || keyPressed == 'b')
		outfile << legend.getSeconds() << " " << keyPressed << std::endl;
}
