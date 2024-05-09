//-----------------------------------------
#include "gamemanager.h"

#include <string>
#include <iostream>

#include "game.h"

#include "simpleboard.h"
#include "consoleplayer.h"
#include "consolegame.h"

#include "uiconsole.h"

//============================================
IGame* GameManager::createGame(const std::string& name) const
{
    ICommonUI* c_ui = new ConsoleUI();
    
    int playersAmt = 0;
    int boardSize = 0, winCondition = 0;
    
    std::string playersPrompt = " number of players\n"
        "1 -- user vs computer\n"
        "2 -- user vs user\n";

    c_ui->cui_readInt(playersAmt, playersPrompt, 0, 3);
    c_ui->cui_readInt(boardSize, "board size (3..N)", 2, -1);
    c_ui->cui_readInt(winCondition,
        "win condition (amount of marks lined up; 3..N)", 2, -1);

    if (winCondition > boardSize) winCondition = boardSize;

    IGame* game = nullptr;
    if (name == "console_game")
    {

        IBoard* board = new SimpleBoard(boardSize);

        game = static_cast<IGame*>(new ConsoleGame(
            "console_game", board,
            c_ui,
            winCondition, playersAmt
        )); // winCondition added; playerAmt added
    }

    return game;
}
