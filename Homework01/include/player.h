#pragma once

#include <string>
#include <iostream>

#include "dice.h"

/**
 * @brief Игрок;
 * он бросает кость и тянет спички из коробки
 */
class Player
{
private:
    bool human = false;
    std::string* name;
    int pID;
    bool inGame = true;
public:
    Player(int);
    Player(std::string);
    ~Player();

    std::string getName();

    bool isInGame();

    void setInGame(bool);

    bool isHuman();



    void matchesAmt(Dice*, int&);

    void matchesAmt(int&);

};