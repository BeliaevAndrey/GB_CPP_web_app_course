#pragma once

#include <iostream>

#include "player.h"
#include "matchbox.h"
#include "dice.h"

/**
 * @brief Класс игра
 * управляет ходом игры
 */
class Game {
private:
    Player** players;
    MatchBox* matchBox;
    Dice* dice;
    int playersAmt;
    int playersOut = 0;
    int usersAmt = 0;
    void askName(std::string&);
    void move(Player*);
    void mixPlayers();

public:
    Game(int);
    Game(int, int);
    ~Game();

    void play();
};
