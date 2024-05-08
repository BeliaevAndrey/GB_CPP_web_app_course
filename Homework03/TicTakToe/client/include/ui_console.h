#ifndef UI_CONSOLE_H
#define UI_CONSOLE_H
// =====================

#include <iostream>
#include <string>

#include "ui_common.h"

class ConsoleUI : public CommonUI
{
private:
    std::string game_name;
    std::unique_ptr<IBoard> o_board;
    std::vector<std::unique_ptr<IPlayer>> o_players;
    int marksInRow; // win conditions
    int playersAmt; // user vs computer or user vs user 

public:
    ConsoleUI() = default;
    ~ConsoleUI() = default;


    virtual int readInt(
        int& param, std::string prompt,
        int lowerLim, int uppperLim) const override;

    virtual std::string readString(std::string prompt) const override;

    virtual void printMsg(std::string message) const override;

    virtual void renderBoard() const override;

protected:
    std::string name() const;

};


// ========================
#endif // CONSOLEUI_H
