#include "ship.h"
//moving a ships data 
void Ship::moveShip(int direction, char(&board)[25][81])
{
	int l, j;
	switch (tolower(direction))
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
		return;
	}
	for (int i = 0; i < size; i++)
		pos[i].set(pos[i].getX() + j, pos[i].getY() + l);
}
//drawing a ship on the board
void Ship::drawShip(char shipType, char(&board)[25][81], bool silent)
{
	for (int i = 0; i < this->size; i++)
	{
		gotoxy(pos[i].getX(), pos[i].getY());
		if (!silent) { std::cout << shipType; }
		board[pos[i].getY()][pos[i].getX()] = shipType;
	}
}
//earsing a ship from the board
void Ship::eraseShip(char(&board)[25][81], bool silent)
{
	for (int i = 0; i < this->size; i++)
	{
		gotoxy(pos[i].getX(), pos[i].getY());
		if (!silent) { std::cout << " "; }
		board[pos[i].getY()][pos[i].getX()] = ' ';
	}
}

//removing the ship from the board after win
void Ship::moveShipToWinningPosition(char(&board)[25][81])
{
	if (this->size == 2)
	{
		this->pos[0].set(75, 2);
		this->pos[1].set(74, 2);
		this->moveShip('z', board);
		this->eraseShip(board);
	}
	else
	{
		this->pos[0].set(77, 2);
		this->pos[1].set(78, 1);
		this->pos[2].set(77, 2);
		this->pos[3].set(78, 1);
		this->moveShip('z', board);
		this->eraseShip(board);
	}
	setIsInX(true);
}

