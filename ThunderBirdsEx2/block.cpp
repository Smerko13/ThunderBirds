#include "block.h"

//moving a blocks data
void Block::moveBlock(char direction, char(&board)[25][81])
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
//drawing a block in the presented board
void Block::drawBlock(char(&board)[25][81],bool silent)
{
	for (int i = 0; i < this->size; i++)
	{
		gotoxy(pos[i].getX(), pos[i].getY());
		if (!silent) { std::cout << this->type; }
		board[pos[i].getY()][pos[i].getX()] = this->type;
	}
}
//earasig a block in the presented board
void Block::eraseBlock(char(&board)[25][81],bool silent)
{
	for (int i = 0; i < this->size; i++)
	{
		gotoxy(pos[i].getX(), pos[i].getY());
		if (!silent) { std::cout << ' '; }
		board[pos[i].getY()][pos[i].getX()] = ' ';
	}
}