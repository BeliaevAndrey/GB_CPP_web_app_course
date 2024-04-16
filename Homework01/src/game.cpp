#include "game.h"

/**
 * @brief Кнструктор игры с участием пользователя
 * 
 * @param playersAmt  -- общее количество игроков
 * @param users       -- количество игроков-пользоавтелей
 */
Game::Game(int playersAmt, int users)
{
    this->playersAmt = playersAmt;
    this->matchBox = new MatchBox(playersAmt * 20);
    this->dice = new Dice;
    this->usersAmt = users;
    players = new Player * [playersAmt];

    for (int i = 0; i < users; i++)
    {
        std::string name;
        askName(name);
        players[i] = new Player(name);
    }

    for (int i = users; i < playersAmt; i++)
    {
        players[i] = new Player(i + 1);
    }

    if (playersAmt > 2) {
        mixPlayers();
    }

}
/**
 * @brief Конструктор игры без участия пользователя
 * 
 * @param playersAmt -- общее количество игроков
 */
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

/* смешать последовательность игроков */
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

/* Ввод имени пользователя */
void Game::askName(std::string& name) {
    std::cout << "Input player name: ";
    std::cin >> name;
}

/**
 * @brief Общий ход игры
 *  
 */
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

/**
 * @brief ход игрока
 * 
 * @param player -- ссылка на участника
 */
void Game::move(Player* player) {
    int count(0);

    if (player->isUser()) player->matchesAmt(count);
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
