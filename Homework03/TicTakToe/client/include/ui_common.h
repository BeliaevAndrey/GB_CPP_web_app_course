#ifndef UI_COMMON_H
#define UI_COMMON_H
// =====================

#include <iostream>
#include <string>
#include <memory>
#include <vector>

#include "board.h"
#include "player.h"
#include "game.h"

class CommonUI
{

public:

    CommonUI() = default;
    ~CommonUI() = default;

    virtual int readInt(
        int& param, std::string prompt, 
        int lowerLim, int uppperLim) const = 0;
    virtual std::string readString(std::string) const = 0;
    virtual void printMsg(std::string message) const = 0;
    virtual void renderBoard() const = 0;

};


// ========================
#endif // COMMONUI_H
