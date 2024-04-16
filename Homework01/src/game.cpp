#include "game.h"


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

}
Game::~Game() {
    delete matchBox;
    for (int i = 0; i < playersAmt; i++)
    {
        delete players[i];
    }
    delete players;
}

void Game::play()
{
    int winner;
    while (playersAmt - playersOut > 1)
    {
        for (int i = 0; i < playersAmt; i++)
        {
            if (players[i]->isInGame())
            {
                winner = i;
                move(players[i]);
                // int count = players[i]->throwDice();
                // players[i]->setInGame(matchBox->pullMatch(count));
                // if (!players[i]->isInGame()) {
                //     playersOut++;
                //     std::cout << players[i]->getName()
                //         << " is out of game. Players left: "
                //         << playersAmt - playersOut
                //         << std::endl;
                // }
            }
        }
    }
    std::cout << players[winner]->getName() << " wins!" << std::endl;
}

void Game::move(Player* player) {

    int count = player->throwDice(dice);
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