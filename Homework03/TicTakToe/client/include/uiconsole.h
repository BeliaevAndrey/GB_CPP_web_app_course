#ifndef UICONSOLE_H
#define UICONSOLE_H
//====================

#include <iostream>

#include "game.h"

#include "uicommon.h"

class ConsoleUI : public ICommonUI

{
private:
    // IGame* m_game;

public:
    ConsoleUI() = default;
    ~ConsoleUI() = default;

    virtual void renderBoard(IGame* game) const override;
    virtual void cui_readInt(int&, std::string, int, int) const override;
    virtual void readString(std::string&, std::string) const override;
    virtual void printMsg(std::string) const override;



};


void ConsoleUI::renderBoard(IGame* m_game) const
{
    std::cout << "render  board called" << std::endl;
    auto dimensions = m_game->board()->dimension();
    const auto& xmin = dimensions.first.x;
    const auto& ymin = dimensions.first.y;
    const auto& xmax = dimensions.second.x;
    const auto& ymax = dimensions.second.y;

    IBoard::PositionType pos;
    for (auto y = ymin; y < ymax; y++)
    {
        pos.y = y;
        for (auto x = xmin; x < xmax; x++)
        {
            pos.x = x;
            auto mark = m_game->board()->mark(pos);
            std::string outSymbol = "_";
            switch (mark)
            {
            case IBoard::MARK_O: outSymbol = "O"; break;
            case IBoard::MARK_X: outSymbol = "X"; break;
            default: break;
            }
            std::cout << "|" << outSymbol << "|";
        }
        std::cout << std::endl;
    }
    std::cout << std::endl;
}

void ConsoleUI::cui_readInt(int& param, std::string prompt,
    int lowerLim, int uppperLim) const
{
    while (true) {
        bool okFlag = true;
        std::string tmp;
        std::cout << "Input " << prompt << ": ";
        std::cin >> tmp;
        for (int i = 0; i < tmp.size(); i++)
            if (tmp[i] < '0' || tmp[i] > '9')
            {
                okFlag = false;
                break;
            }

        if (okFlag)
        {
            param = std::stoi(tmp);
            if (param > lowerLim && param < uppperLim) return;
            else if (param > 0) return;
        }
        std::cout << "Wrong input." << std::endl;
    }
}

void ConsoleUI::readString(std::string& line, std::string prompt) const
{
    std::cout << "Input " << prompt << ": ";
    std::getline(std::cin, line);
}

void ConsoleUI::printMsg(std::string message) const
{
    std::cout << "========================================" << std::endl;
    std::cout << message << std::endl;
    std::cout << "========================================" << std::endl;
}

//====================
#endif  // UICONSOLE_H