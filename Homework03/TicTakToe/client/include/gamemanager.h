#ifndef GAMEMANAGER_H
#define GAMEMANAGER_H

//----------------------------------------
#include "game.h"

//========================================
class GameManager
{
public:
    GameManager() = default;
    GameManager(const GameManager& other) = delete;
    GameManager(GameManager&& other) = delete;
    GameManager& operator=(const GameManager& other) = delete;
    GameManager& operator==(GameManager&& other) = delete;
    ~GameManager() = default;

    IGame* createGame(const std::string & name) const;

    // additions
    void readInt(unsigned int& , std::string, int) const;
    
};

#endif // GAMEMANAGER_H
