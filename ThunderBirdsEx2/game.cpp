#include "game.h"

int Game::showMenu(int numOfBoards) {
    bool flag = true;
    if (numOfBoards == 0)
    {
        std::cout << "No Board files were found! Please contact support";
        Sleep(2500);
        system("cls");
        return (int)Game::choice::EXIT;
    }
    while (flag)
    {
        int choice = mainMenu.showMainMenu();
        if (choice==1) {
            //choose which board to start
            boardChoice = mainMenu.boardChoiceMenu(matchingFiles.size());
            if (boardChoice == 1)
            {
                chosenMode = Game::choice::FULL_GAME;
                return (int)Game::choice::FULL_GAME;
            }
            else
            {
                chosenMode = Game::choice::SINGLE_LEVEL;
                return (int)Game::choice::SINGLE_LEVEL;
            }
        }
        else if (choice == 9)
        {
            mainMenu.printBye();
            flag = false;
        } 
    }
    return (int)Game::choice::EXIT;
}

void Game::play(playingMode mode) {
    gameCounter = 0;
    std::ofstream outFile;
    if (mode == playingMode::SAVE) { deletePrevMoves(); }
    bool flag = true;
    int gamePath;
    while (flag) {
        std::string saveFileName;
        if (chosenMode == Game::choice::SINGLE_LEVEL)//preparing board and save files for single game
        {
            Board tempBoard;
            tempBoard.init(matchingFiles[boardChoice-2]);
            board = tempBoard;
            saveFileName = getSaveFileName(boardChoice - 1);
        }
        else if (chosenMode == Game::choice::FULL_GAME)//preparing board and save files for a full run
        {
            Board tempBoard;
            tempBoard.init(matchingFiles[boardChoice - 1]);
            board = tempBoard;
            boardChoice++;
            saveFileName = getSaveFileName(boardChoice-1);
        }
        system("cls");
        board.show();
        if (mode == playingMode::SAVE) { 
            prepFile(outFile,saveFileName); 
            gamePath = board.play(livesLeft, outFile, mode);
        }
        else
            gamePath = board.play(livesLeft,outFile);
        if (gamePath == 0)//case we lost
        {
            livesLeft--;
            system("cls");
            if (livesLeft > 0) { mainMenu.printTryAgain(); }
            if (chosenMode == Game::choice::FULL_GAME)
            {
                boardChoice--;
                gameCounter--;
            }
        }
        else if (gamePath == 3)//case pressed exit from pause menu
        {
            break;
        }
        else
        {
            if (chosenMode == Game::choice::SINGLE_LEVEL)
            {
                mainMenu.printWin();
                livesLeft = 0;
            }
            else if (chosenMode == Game::choice::FULL_GAME)
            {
                if (gameCounter == matchingFiles.size() - 1) {
                    mainMenu.printWin();
                    flag = false;
                }
                else
                    mainMenu.printNextLevel();
            }
        }
        gameCounter++;
        if (livesLeft == 0)
        {
            flag = false;
            mainMenu.printLoss();
        }
        if (mode == playingMode::SAVE) { outFile.close(); }
    }
    system("cls");
    livesLeft = 3;
}
//looking for files with the name screen in it in order to create a vector that will help us initiate the screens
int Game::initiateVectorOfFileNames()
{
    if (std::filesystem::exists(directory) && std::filesystem::is_directory(directory))
    {
        for (const auto& entry : std::filesystem::directory_iterator(directory))
        {
            if (entry.is_regular_file() && entry.path().extension() == extension &&
                entry.path().filename().string().find("screen") != std::string::npos)
            {
                matchingFiles.push_back(entry.path().filename().string());
            }
        }
    }
    return matchingFiles.size();
}
//dlete previous steps files in order to save new once without overwriting
void Game::deletePrevMoves()
{
    if (std::filesystem::exists(directory) && std::filesystem::is_directory(directory))
    {
        for (const auto& entry : std::filesystem::directory_iterator(directory))
        {
            if (entry.is_regular_file() && entry.path().extension() == extension &&
                entry.path().filename().string().find("steps") != std::string::npos)
            {
                std::filesystem::remove(entry.path());
            }
        }
    }
}
//get the appropriate name of the desired file
std::string Game::getSaveFileName(int index)
{
    std::string returnedName;
    if (index >= 10)
        returnedName = "tb" + std::to_string(index) + ".steps" + ".txt";
    else if (index < 10)
        returnedName = "tb0" + std::to_string(index) + ".steps" + ".txt";
    return returnedName;
}
//helper function to open a file
void Game::prepFile(std::ofstream& outFile, std::string name)
{
    if (fileExists(name))
        outFile.open(name, std::ios::app);
    else
    {
        outFile.open(name);
    }

    if (!outFile)
    {
        system("cls");
        std::cout << "Error handling files!Expect Bugs!";
        Sleep(2500);
    }
}

