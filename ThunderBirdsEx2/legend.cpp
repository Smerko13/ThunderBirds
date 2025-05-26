#include "legend.h"

int Legend::numOfLivesLeft = 3;

bool Legend::getTimeLeftArg()
{
	seconds--;
	if (seconds == ZERO)
		return false;
	else
		return true;
}

void Legend::printTimer() const
{
	gotoxy(pos.getX(),pos.getY());
	std::cout << "Time left: " << seconds <<" ";
	if (seconds < (int)Legend::numOfDigits::Two && seconds >(int)Legend::numOfDigits::One)
		std::cout << " ";
	else if (seconds >= (int)Legend::numOfDigits::Two)
	{
		std::cout << "";
	}
	else
		std::cout << "  ";

	gotoxy(pos.getX(), pos.getY()-1);
	if (activeShip)
		std::cout << "Active Ship: Big Ship  ";
	else
		std::cout << "Active Ship: Small Ship";
	gotoxy(pos.getX(), pos.getY() + 1);
	std::cout << "Lives left: " << numOfLivesLeft<< "          ";
}

void Legend::printPause()
{
	gotoxy(pos.getX(), pos.getY());
	bool pause = true;
	while (pause)
	{
		gotoxy(pos.getX(), pos.getY()-1);
		std::cout << "Game Paused!           ";
		gotoxy(pos.getX(), pos.getY());
		std::cout << "Press 9 to exit        ";
		gotoxy(pos.getX(), pos.getY()+1);
		std::cout<<"Press any key to resume";
		if (_getch() == '9')
		{
			timeLeft = false;
			break;
		}
		else
			pause = false;
	}
}