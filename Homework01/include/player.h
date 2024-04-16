#pragma once

#include <string>

#include "dice.h"

/**
 * @brief Игрок;
 * он бросает кость и тянет спички из коробки
 */
class Player
{
private:
    bool isHuman = false;
    std::string* name;
    int pID;
    bool inGame = true;
public:
    Player(int);
    Player(int, std::string);
    ~Player();

    int throwDice(Dice*);

    std::string getName();

    bool isInGame();

    void setInGame(bool);

};