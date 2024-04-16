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
    int humansAmt = 0;
    void askName(std::string&);
    void move(Player*);
    void mixPlayers();

public:
    Game(int);
    Game(int, int);
    ~Game();

    void play();
};
