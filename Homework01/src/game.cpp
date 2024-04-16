#include "game.h"


Game::Game(int playersAmt, int humans)
{
    this->playersAmt = playersAmt;
    this->matchBox = new MatchBox(playersAmt * 20);
    this->dice = new Dice;
    this->humansAmt = humans;
    players = new Player * [playersAmt];

    for (int i = 0; i < humans; i++)
    {
        std::string name;
        askName(name);
        players[i] = new Player(name);
    }

    for (int i = humans; i < playersAmt; i++)
    {
        players[i] = new Player(i + 1);
    }

    if (playersAmt > 2) {
        mixPlayers();
    }

}
Game::Game(int playersAmt)
{
    this->playersAmt = playersAmt;
    this->matchBox = new MatchBox(playersAmt * 20);
    this->dice = new Dice;
    players = new Player * [playersAmt];

    for (int i = 0; i < playersAmt; i++)
    {
        players[i] = new Player(i + 1);
    }

    if (playersAmt > 2) {
        mixPlayers();
    }
}
Game::~Game() {
    delete matchBox;
    for (int i = 0; i < playersAmt; i++)
    {
        delete players[i];
    }
    delete players;
}

void Game::mixPlayers()
{

    for (int i = 0; i < playersAmt; i++)
    {
        Player* tmp = players[i];
        int k = rand() % playersAmt;
        players[i] = players[k];
        players[k] = tmp;
    }

}

void Game::askName(std::string& name) {
    std::cout << "Input player name: ";
    std::cin >> name;
}

void Game::play()
{
    bool runFlag = true;
    int winner;
    while (runFlag)
    {
        for (int i = 0; i < playersAmt; i++)
        {
            if (players[i]->isInGame())
            {
                winner = i;
                if (playersAmt - playersOut == 1)
                {
                    runFlag = false;
                    break;
                }

                move(players[i]);
            }
        }
    }
    std::cout << players[winner]->getName() << " wins!" << std::endl;
}

void Game::move(Player* player) {
    int count(0);

    if (player->isHuman()) player->matchesAmt(count);
    else player->matchesAmt(dice, count);

    std::cout << player->getName() << " pulls "
        << count << " of matches."
        << std::endl;

    player->setInGame(matchBox->pullMatch(count));

    if (!player->isInGame()) {
        playersOut++;
        std::cout << player->getName()
            << " is out of game. Players left: "
            << playersAmt - playersOut
            << std::endl;
    }
}