#pragma once

#include <string>
#include <iostream>

#include "dice.h"

/**
 * @brief Игрок;
 * бросает кость (автоматический игрок);
 * запрашивает количество спичек (игрок-пользователь);
 * тянет спички из коробки 
 */
class Player
{
private:
    bool user = false;
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

    bool isUser();



    void matchesAmt(Dice*, int&);

    void matchesAmt(int&);

};
