#include "menu.h"
using namespace std;

int Menu::showMainMenu()
{
	cout << "Welcome to ThunderBirds! Please choose an option below:" << endl;
	cout << endl << "(1) Start a new game" << endl << "(8) Present instructions and keys" << endl << "(9) EXIT" << endl << endl;;

	bool flag = true;
	int keypressed = _getch();
	switch (keypressed) {
	case '1':
		system("cls");
		return (int)Menu::decisions::Play;
		break;
	case '8':
		system("cls");
		cout << "KEYS:" << endl << endl;
		cout << "LEFT:  a or A" << endl;
		cout << "RIGHT: d or D" << endl;
		cout << "UP:    w or W" << endl;
		cout << "DOWN:  x or X" << endl << endl;
		cout << "Switch to big ship: b or B (In case you were already using this ship, just stops it)" << endl;
		cout << "Switch to small ship: s or S (In case you were already using this ship, just stops it)" << endl;
		cout << endl << "Enter any key to continue" << endl;
		while (flag)
		{
			if (_kbhit())
				flag = false;
		}
		return (int)Menu::decisions::Return;
		break;
	case '9':
		return (int)Menu::decisions::Exit;
		break;
	default:
		system("cls");
		return (int)Menu::decisions::Return;
		break;
	}
}
void Menu::printWin() {
	std::string win =
		"Congratulations! You won!\n";
	system("cls");
	std::cout << win << std::endl;
	Sleep(2500);
	system("cls");
	//showMainMenu();
}
void Menu::printNextLevel() {
	std::string nextLvl =
		"Congratulations! Passed to the next level!\n";
	system("cls");
	std::cout << nextLvl << std::endl;
	Sleep(2500);
	system("cls");
	//showMainMenu();
}
void Menu::printLoss() {
	std::string loss =
		"Game Over!\n";
	system("cls");
	std::cout << loss << std::endl;
	Sleep(2500);
	system("cls");
	//showMainMenu();
}
void Menu::printBye() {
	std::string bye =
		"Thanks for playing!\n";
	system("cls");
	std::cout << bye << std::endl;
	Sleep(1500);
	system("cls");
}
void Menu::printTryAgain() {
	std::string tryAgain =
		"Lost a life! Try again!\n";
	system("cls");
	std::cout << tryAgain << std::endl;
	Sleep(2500);
	system("cls");

}
int Menu::boardChoiceMenu(int numOfLevels)
{
	cout << "Please choose an option below : " << endl;
	cout << endl << "(1)Run full game" << endl;
	for (int i = 0; i < numOfLevels; i++)
	{
		cout << "(" << i + 2 << ")" << "Run level " << i + 1<<endl;
	}
	bool flag = true;
	while (flag)
	{
		int keyPressed = _getch() -'0';
		if (keyPressed >= 1 && keyPressed <= numOfLevels + 1)
		{
			system("cls");
			return keyPressed;
		}
	}
}
