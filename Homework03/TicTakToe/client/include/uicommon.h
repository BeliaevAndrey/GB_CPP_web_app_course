#ifndef UICOMMON_H
#define UICOMMON_H
//====================

#include <string>

#include "board.h"

class ICommonUI
{
public:
    ICommonUI() = default;
    ~ICommonUI() = default;

    virtual void renderBoard(IGame* game) const = 0;
    virtual void cui_readInt(int&, std::string, int, int) const = 0;
    virtual void readString(std::string&, std::string) const = 0;
    virtual void printMsg(std::string) const = 0;

};

//====================
#endif  // UICOMMON_H