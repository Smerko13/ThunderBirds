#pragma once
#include <iostream>
#include "general.h"
#include <conio.h>
#include <Windows.h>

class Menu
{
	enum class decisions {Play=1,Return=8,Exit=9};
public:
	int showMainMenu();
	int boardChoiceMenu(int numOfLevels);
	void  printWin();
	void  printLoss();
	void  printBye();
	void  printTryAgain();
	void  printNextLevel();
};

