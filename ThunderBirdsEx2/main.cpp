#include "Game.h"
#include "gameLoad.h"
#include <windows.h>
#include <cstring>


void hideCursor() {
	HANDLE consoleHandle = GetStdHandle(STD_OUTPUT_HANDLE);
	CONSOLE_CURSOR_INFO info;
	info.dwSize = 100;
	info.bVisible = FALSE;
	SetConsoleCursorInfo(consoleHandle, &info);
}


int main(int argv,char* argc[])
{
	hideCursor(); 
	
	if (argv == 1)//playing the game in regular mode
	{
		Game theGame;
		int numOfBoards = theGame.initiateVectorOfFileNames();
		while (theGame.showMenu(numOfBoards))
			theGame.play();
	}
	else if (strcmp(argc[1], "-save") == 0)//playing the game in save mode
	{
		Game theGame;
		int numOfBoards = theGame.initiateVectorOfFileNames();
		std::cout << "Runnig game on save mode";
		Sleep(1500);
		system("cls");
		while (theGame.showMenu(numOfBoards))
			theGame.play(playingMode::SAVE);
	}
	else if(strcmp(argc[1],"-load")==0&&argv==2)//playing the game in load mode
	{
		GameLoad theGame;
		int numOfBoards = theGame.initiateVectorOfFileNames();
		std::cout << "Runnig game on load mode";
		Sleep(1500);
		system("cls");
		theGame.playLoaded();
	}
	else if (strcmp(argc[1], "-load") == 0 && strcmp(argc[2],"-silent")==0 && argv == 3)//playing the game in silent load mode
	{
		GameLoad theGame;
		int numOfBoards = theGame.initiateVectorOfFileNames();
		std::cout << "Runnig game on load silent mode";
		Sleep(1500);
		system("cls");
		theGame.playLoadedSilent();
	}
	else // case an inappropriate game mode was trying to be loaded
	{
		std::cout << "Error loading required game mode! Please contact support";
		Sleep(2500);
		system("cls");
	}
}