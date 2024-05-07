
#include "aiplayer.h"

//---------------------------------
#include <optional>
#include <iostream>

//=================================
std::string AIPlayer::name() const
{
    return m_name;
}

std::optional<IBoard::PositionType> AIPlayer::getMove(uint64_t /*timeout = -1*/) const
{

//     std::cout << "player " << name() << " enter your move: " << std::endl;
//     IBoard::PositionType pos;
//     std::cout << "x: ";
//     std::cin >> pos.x;
//     std::cout << "y: ";
//     std::cin >> pos.y;
//
//     return pos;
// }
//
// IBoard::PositionType AIPlayer::calculateMove()
// {
    
    
    auto dimensions = m_game->board()->dimension();
    const auto& xmin = dimensions.first.x;
    const auto& ymin = dimensions.first.y;
    const auto& xmax = dimensions.second.x;
    const auto& ymax = dimensions.second.y;

    int count_x;
    int count_o;
    IBoard::PositionType pos;
    IBoard::PositionType newPos;

    //  check rows
    for (int i = ymin; i < ymax; i++)
    {
        // todo: add abilities to add mark at rows start-points
        count_x = 0;
        count_o = 0;
        pos.y = i;  // row
        for (int j = xmin; j < xmax; j++)
        {
            pos.x = j;   // col
            auto mark = m_game->board()->mark(pos);
            switch (mark)
            {
            case  IBoard::MARK_X:
            {
                count_x++;
                count_o = 0;
                if (count_x == m_game->getMarksInRow() - 1) {
                    ++pos.x;
                    return pos;
                }
                break;
            }
            case IBoard::MARK_O:
            {
                count_o++;
                count_x = 0;
                if (count_o == m_game->getMarksInRow() - 1) {
                    ++pos.x;
                    return pos;
                }
                break;
            }
            case IBoard::MARK_EMPTY:
            {
                count_x = 0;
                count_o = 0;
                break;
            }

            default: break;
            }
        }
    }

    // check columns
    for (auto i = xmin; i < xmax; i++)
    {
        // todo: add abilities to add mark at rows start-points
        count_x = 0;
        count_o = 0;
        pos.x = i;
        for (auto j = ymin; j < ymax; j++)
        {
            pos.y = j;
            auto mark = m_game->board()->mark(pos);
            switch (mark) {
            case IBoard::MARK_X:
            {
                count_x++;
                count_o = 0;
                if (count_x == m_game->getMarksInRow() - 1)
                {
                    pos.y++;
                    return pos;
                }
                break;
            }

            case IBoard::MARK_O:
            {
                count_o++;
                count_x = 0;
                if (count_o == m_game->getMarksInRow() - 1)
                {
                    pos.y++;
                    return pos;
                }
                break;
            }

            case IBoard::MARK_EMPTY:
            {
                count_x = 0;
                count_o = 0;
                break;
            }

            default: break;
            }
        }
    }

    // check left to right diagonal
    count_x = 0;
    count_o = 0;
    for (int i = xmin; i < xmax; i++)
    {
        // todo: add abilities to add mark at rows start-points
        pos.x = i;
        pos.y = i;
        auto mark = m_game->board()->mark(pos);
        switch (mark) {
        case IBoard::MARK_X:
        {
            count_x++;
            count_o = 0;
            if (count_x == m_game->getMarksInRow() - 1){
                 pos.x++;
                 pos.y++;
                 return pos;
                 }
            break;
        }

        case IBoard::MARK_O:
        {
            count_o++;
            count_x = 0;
            if (count_o == m_game->getMarksInRow() - 1) {
                pos.x++;
                pos.y++;
                return pos;
                }
            break;
        }

        case IBoard::MARK_EMPTY:
        {
            count_x = 0;
            count_o = 0;
            break;
        }

        default: break;
        }
    }

    // check right to left diagonal
    for (int i = xmin; i < xmax; i++)
    {
        // todo: add abilities to add mark at rows start-points
        pos.x = xmax - i - 1;
        pos.y = i;
        auto mark = m_game->board()->mark(pos);
        switch (mark) {
        case IBoard::MARK_X:
        {
            count_x++;
            count_o = 0;
            if (count_x == m_game->getMarksInRow() - 1 && pos.x > xmin) {
                pos.x--;
                pos.y++;
                return pos;
            }
            break;
        }
        case IBoard::MARK_O:
        {
            count_o++;
            count_x = 0;
            if (count_o == m_game->getMarksInRow() - 1 && pos.x > xmin) {
                pos.x--;
                pos.y++;
                return pos;
                }
            break;
        }

        case IBoard::MARK_EMPTY:
        {
            count_x = 0;
            count_o = 0;
            break;
        }

        default: break;
        }
    }

    // In case of empty board place mark to board center position

    pos.x = xmax / 2;
    pos.y = ymax / 2;
    return pos;

}
