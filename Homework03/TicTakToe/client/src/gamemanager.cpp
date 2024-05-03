//-----------------------------------------
#include "gamemanager.h"

#include <string>
#include <iostream>

#include "game.h"

#include "simpleboard.h"
#include "consoleplayer.h"
#include "consolegame.h"

void GameManager::readInt(int& param,
    std::string paramName = "param") const
{
    while (true) {
        std::string tmp;
        std::cout << "Input " << paramName << ": ";
        std::cin >> tmp;
        for (int i=0; i < tmp.size(); i++)
            if (tmp[i] > '0' && tmp[i] <= '9')
            {
                param = std::stoi(tmp);
                return;
            }
    }
}

//============================================
IGame* GameManager::createGame(const std::string& name) const
{
    int boardSize, winCondition;
    readInt(boardSize, "board size");
    readInt(winCondition, "win condition (amt of marks inline)");
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

// int GameManager::readBoardSize() {
//     int bSize;
//     std::cout << "Input board size: ";
//     std::cin >> bSize;
//     return bSize;
// }
//
// int GameManager::readWinConditions() {
//     int marksInline;
//     std::cout 
//     << "Input how many marks should be inline for win: ";
//     std::cin >> marksInline;
//     return marksInline;
// }

