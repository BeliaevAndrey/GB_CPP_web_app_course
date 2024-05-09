#ifndef GAMEMANAGER_H
#define GAMEMANAGER_H

//----------------------------------------
#include "game.h"
#include "uicommon.h"

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

    IGame* createGame(const std::string & name, ICommonUI* ui) const;
  
};

#endif // GAMEMANAGER_H
