#pragma once


#include "Board.h"
#include "menu.h"
#include <vector>
#include <iostream>
#include <filesystem>
#include <string>

class Game {
private:
protected:
    enum class choice{FULL_GAME=1,SINGLE_LEVEL=2,EXIT=0};
    choice chosenMode;
    Board board;
    std::string directory = ".";
    std::string extension = ".txt";
    std::vector<std::string> matchingFiles;
    Menu mainMenu;
    int livesLeft = 3;
    int boardChoice;
    int gameCounter = 0;
public:
    int showMenu(int numOfBoards);
    void play(playingMode mode = playingMode::REGULAR);
    int initiateVectorOfFileNames();
    void deletePrevMoves();
    std::string getSaveFileName(int index);
    void prepFile(std::ofstream& outFile,std::string name);
    bool fileExists(const std::string& filename) {
        std::ifstream file(filename);
        return file.good();
    }
};

