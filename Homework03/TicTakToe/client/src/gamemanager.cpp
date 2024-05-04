//-----------------------------------------
#include "gamemanager.h"

#include <string>
#include <iostream>

#include "game.h"

#include "simpleboard.h"
#include "consoleplayer.h"
#include "consolegame.h"

//============================================
IGame* GameManager::createGame(const std::string& name) const
{
    unsigned int boardSize, winCondition;
    readInt(boardSize, "board size");
    readInt(winCondition,
        "win condition (amount of marks lined up)");
    if (winCondition > boardSize) winCondition = boardSize;

    IGame* game = nullptr;
    if (name == "console_game")
    {
        IBoard* board = new SimpleBoard(boardSize);
        game = static_cast<IGame*>(new ConsoleGame
        ("console_game", board, winCondition)); // winCondition added
    }

    return game;
}


// additions

void GameManager::readInt(unsigned int& param,
    std::string paramName = "param") const
{
    while (true) {
        bool okFlag = true;
        std::string tmp;
        std::cout << "Input " << paramName << ": ";
        std::cin >> tmp;
        for (int i = 0; i < tmp.size(); i++)
            if (tmp[i] < '0' || tmp[i] > '9')
            {
                okFlag = false;
                break;
            }

        if (okFlag)
        {
            param = std::stoi(tmp);
            if (param > 0) return;
        }
        std::cout << "Wrong input." << std::endl;
    }
}
