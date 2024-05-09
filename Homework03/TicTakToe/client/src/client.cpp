//----------------------------------------------

#include <string>
#include <vector>
#include <optional>
#include <utility>
#include <vector>
#include <memory> 

#include "board.h"
#include "player.h"
#include "game.h"

#include "gamemanager.h"
#include "gamemanager.h"
#include "uicommon.h"
#include "uiconsole.h"

//[5]============================================================================
int main(int argv, char* argc[])
{
    ICommonUI* c_ui = new ConsoleUI();
    GameManager gameManager;

    while (true) {

        c_ui->printMsg("Tic-Tac-Toe game");

        std::unique_ptr<IGame> game;

        int answer = 0;
        std::string prompt = "Create local game?\n1. Yes\n2. No\n";
        c_ui->cui_readInt(answer, prompt, 0, 3);

        switch (answer)
        {
        case 1:
        {
            c_ui->printMsg("Creating game");
            game.reset(gameManager.createGame("console_game", c_ui));
        }
        break;
        case 2:
            return 0; //exit program
        default: break;
        }

        if (game)
        {
            c_ui->printMsg("Game created");
            if (game->waitForPlayers(30000))
                game->exec();
        }
        else
            c_ui->printMsg("Game NOT created");
    }

    return 0;
}

//[6]================================================================
