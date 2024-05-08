#include "ui_console.h"

int ConsoleUI::readInt(int& param, std::string prompt,
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

std::string ConsoleUI::readString(std::string prompt) const
{
    std::string line;
    std::cout << "Input " << prompt << ": ";
    std::getline(std::cin, line);
    return line;

}

void ConsoleUI::printMsg(std::string message) const
{
    std::cout << "========================================" << std::endl;
    std::cout << message << std::endl;
    std::cout << "========================================" << std::endl;
}

void ConsoleUI::renderBoard() const
{
    auto dimensions = o_board->dimension();
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
            auto mark = o_board->mark(pos);
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

std::string ConsoleUI::name() const { return game_name; }
