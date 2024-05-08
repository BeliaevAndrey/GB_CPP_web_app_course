
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

    std::cout << name() << " is making move..." << std::endl;

    auto dimensions = m_game->board()->dimension();
    const auto& xmin = dimensions.first.x;
    const auto& ymin = dimensions.first.y;
    const auto& xmax = dimensions.second.x;
    const auto& ymax = dimensions.second.y;

 
    int dlt[] = { 1, 0, -1 };

    IBoard::PositionType pos, tmpPos;

    for (int y = 0; y < ymax; y++)
    {
        for (int x = 0; x < xmax; x++)
        {
            pos.x = x;
            pos.y = y;

            auto mark = m_game->board()->mark(pos);

            if (mark == IBoard::MARK_X || mark == IBoard::MARK_O)
                for (int i = 0; i < 3; i++)
                {
                    for (int j = 0; j < 3; j++)
                    {

                        tmpPos.x = (pos.x + dlt[j] < xmax &&
                            pos.x + dlt[j] > xmin) ?
                            pos.x + dlt[j] : pos.x;

                        tmpPos.y = (pos.y + dlt[i] < ymax &&
                            pos.y + dlt[i] > ymin) ?
                            pos.y + dlt[i] : pos.y;

                        if (m_game->board()->mark(tmpPos) == IBoard::MARK_EMPTY)
                            return tmpPos;
                    }
                }
        }
    }

    return pos;

}
