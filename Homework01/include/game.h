#pragma once

#include <iostream>

#include "player.h"
#include "matchbox.h"
#include "dice.h"

class Game {
private:
    Player** players;
    MatchBox* matchBox;
    Dice* dice;
    int playersAmt;
    int playersOut = 0;

public:
    Game(int playersAmt);
    ~Game();

    void play();
    void move(Player*);
};
