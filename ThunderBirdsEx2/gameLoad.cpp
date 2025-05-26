#include "GameLoad.h"
//playing in regular/save mode
void GameLoad::playLoaded()
{
    livesLeft = 3;
    int gamePath;
    int index = 0;
    bool winFlag = false;
    std::streampos pos;
    initiateVectorOfLoadFileNames("steps",loadFiles);
    if (loadFiles.size() != matchingFiles.size()) {
        std::cout << "Not enough save files to run a fully loaded game!";
        Sleep(2500);
        return;
    }
    else {
        for (index; index < loadFiles.size();)
        {
            std::ifstream inFile(loadFiles[index]);
            inFile.seekg(0, std::ios::beg);
            if (!inFile)
            {
                std::cout << "Error while hadling files! Expect bugs!";
                return;
            }
            else
            {
                bool flag = true;
                while (flag)
                {
                    inFile.seekg(pos);
                    BoardLoad tempBoard;
                    tempBoard.init(matchingFiles[index]);
                    boardLoad = tempBoard;
                    system("cls");
                    boardLoad.show();
                    gamePath = boardLoad.playLoaded(livesLeft, inFile);
                    pos = inFile.tellg();
                    if (gamePath == 0)
                    {
                        livesLeft--;
                        system("cls");
                        if (livesLeft > 0) { mainMenu.printTryAgain(); pos = inFile.tellg(); }
                        if (livesLeft == 0) {
                            mainMenu.printLoss();
                            flag = false;
                            winFlag = true;
                        }
                    }
                    else if (gamePath == 1)
                    {
                        if (index == loadFiles.size() - 1)
                        {
                            mainMenu.printWin();
                            flag = false;
                            winFlag = true;
                        }
                        else
                        {
                            flag = false;
                            mainMenu.printNextLevel();
                            index++;
                            pos = 0;
                        }
                        break;//infileclose
                    }
                    else if (gamePath == 2)
                    {
                        livesLeft--;
                    }
                    else if (gamePath == 3)
                        flag = false;
                }
                if (gamePath == 3 || winFlag)
                {
                    mainMenu.printBye();
                    break;
                }
            }
            inFile.close();
        }
    }
}
//running the game replay silent mode
void GameLoad::playLoadedSilent()
{
    livesLeft = 3;
    int gamePath;
    int index = 0;
    bool winFlag = false;
    std::streampos pos;
    initiateVectorOfLoadFileNames("steps", loadFiles);
    if (loadFiles.size() != matchingFiles.size()) {
        std::cout << "Not enough save files to run a fully loaded game!";
        Sleep(2500);
        return;
    }
    else {
        for (index; index < loadFiles.size();)
        {
            std::ifstream inFile(loadFiles[index]);
            inFile.seekg(0, std::ios::beg);
            if (!inFile)
            {
                std::cout << "Error while hadling files! Expect bugs!";
                return;
            }
            else
            {
                bool flag = true;
                while (flag)
                {
                    inFile.seekg(pos);
                    BoardLoad tempBoard;
                    tempBoard.init(matchingFiles[index]);
                    boardLoad = tempBoard;
                    gamePath = boardLoad.playLoadedSilent(livesLeft, inFile, resultsLoaded);
                    pos = inFile.tellg();
                    if (gamePath == 0)
                    {
                        livesLeft--;
                        if (livesLeft > 0) { pos = inFile.tellg(); }
                        if (livesLeft == 0) {
                            flag = false;
                            winFlag = true;
                        }
                    }
                    else if (gamePath == 1)
                    {
                        if (index == loadFiles.size() - 1)
                        {
                            flag = false;
                            winFlag = true;
                        }
                        else
                        {
                            flag = false;
                            index++;
                            pos = 0;
                        }
                        break;//infileclose
                    }
                    else if (gamePath == 2)
                    {
                        livesLeft--;
                    }
                    else if (gamePath == 3)
                        flag = false;
                }
                if (gamePath == 3 || winFlag)
                {
                    break;
                }
            }
            inFile.close();
        }
    }
    //check if matching the files
    checkResult();
}
//iniate a vector for diffrent file names
void GameLoad::initiateVectorOfLoadFileNames(const char* identity, std::vector<std::string>& vector)
{
    if (std::filesystem::exists(directory) && std::filesystem::is_directory(directory))
    {
        for (const auto& entry : std::filesystem::directory_iterator(directory))
        {
            if (entry.is_regular_file() && entry.path().extension() == extension &&
                entry.path().filename().string().find(identity) != std::string::npos)
            {
                vector.push_back(entry.path().filename().string());
            }
        }
    }
}
//checking the result at the end of a silent run
void GameLoad::checkResult()
{
    int i = 0;
    std::string compare;
    std::streampos pos;
    initiateVectorOfLoadFileNames("result", resultFiles);
    int index = 0; 
    for (; index < resultFiles.size();)
    {
        std::ifstream resFile(resultFiles[index]);
        while (i < resultsLoaded.size() &&resFile >> compare)
        {
            if (compare != resultsLoaded[i])
            {
                system("cls");
                std::cout << "Test failed!";
                Sleep(2500);
                return;
            }
            i++;
        }
        if(index!=resultFiles.size()-1)
            resFile.close();
        else
        {
            pos = resFile.tellg();
            resFile.close();
        }
        index++;
    }
    std::ifstream resFile(resultFiles[index - 1]);
    resFile.seekg(pos);
    if (resFile >> compare)
    {
        system("cls");
        std::cout << "Test failed!";
        Sleep(2500);
    }
    else if(i==resultsLoaded.size())
    {
        system("cls");
        std::cout << "Test Succeeded!";
        Sleep(2500);
    }
    else
    {
        system("cls");
        std::cout << "Test failed!";
        Sleep(2500);
    }
    resFile.close();
}