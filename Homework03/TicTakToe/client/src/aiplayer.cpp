
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

    // check rows
    tmpPos = checkRows(xmin, xmax, ymin, ymax);
    if (tmpPos.x < xmax && tmpPos.y < ymax) return tmpPos;

    // check columns
    tmpPos = checkCols(xmin, xmax, ymin, ymax);
    if (tmpPos.x < xmax && tmpPos.y < ymax) return tmpPos;

    // other check
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


IBoard::PositionType AIPlayer::checkRows(
    int lo_x, int up_x, int lo_y, int up_y) const
{
    std::map<int, int> map_x;
    std::map<int, int> map_o;

    IBoard::PositionType pos;

    for (int i = lo_y; i < up_y; i++)
    {
        int count_x = 0;
        int count_o = 0;
        pos.y = i;
        for (int j = lo_x; j < up_x; j++)
        {
            pos.x = j;
            auto mark = m_game->board()->mark(pos);
            if (mark == IBoard::MARK_X)
            {
                count_x++;
                count_o = 0;
                if (!map_x[i]) map_x[i] = count_x;
                else if (count_x > map_x[i]) map_x[i] = count_x;
            }
            else if (mark == IBoard::MARK_O)
            {
                count_o++;
                count_x = 0;
                if (!map_o[i]) map_o[i] = count_o;
                else if (count_o > map_o[i]) map_o[i] = count_o;
            }
            else if (mark == IBoard::MARK_EMPTY)
            {
                if (!map_x[i]) map_x[i] = count_x;
                else if (count_x > map_x[i]) map_x[i] = count_x;

                if (!map_o[i]) map_o[i] = count_o;
                else if (count_o > map_o[i]) map_o[i] = count_o;

                count_x = 0;
                count_o = 0;
            }
        }
    }

    std::pair<int, int> max_x = getMaxOfMap(map_x);
    std::pair<int, int> max_o = getMaxOfMap(map_o);
    int winCondition = m_game->getMarksInRow();

    if (max_o.first == winCondition - 1) {
        pos.y = max_o.second;
        for (int i = lo_x; i < up_x; i++)
        {
            pos.x = i;
            auto mark = m_game->board()->mark(pos);
            if (mark == IBoard::MARK_EMPTY)
                return pos;
        }
    }

    if (max_x.first == winCondition - 1) {
        pos.y = max_x.second;
        for (int i = lo_x; i < up_x; i++)
        {
            pos.x = i;
            auto mark = m_game->board()->mark(pos);
            if (mark == IBoard::MARK_EMPTY)
                return pos;
        }
    }
    
    pos.x = -1;
    pos.y = -1;
    return pos;
}



IBoard::PositionType AIPlayer::checkCols(
    int lo_x, int up_x, int lo_y, int up_y) const
{
    std::map<int, int> map_x;
    std::map<int, int> map_o;

    IBoard::PositionType pos;

    for (int i = lo_y; i < up_y; i++)
    {
        int count_x = 0;
        int count_o = 0;
        pos.x = i;
        for (int j = lo_x; j < up_x; j++)
        {
            pos.y = j;
            auto mark = m_game->board()->mark(pos);
            if (mark == IBoard::MARK_X)
            {
                count_x++;
                count_o = 0;
                if (!map_x[i]) map_x[i] = count_x;
                else if (count_x > map_x[i]) map_x[i] = count_x;
            }
            else if (mark == IBoard::MARK_O)
            {
                count_o++;
                count_x = 0;
                if (!map_o[i]) map_o[i] = count_o;
                else if (count_o > map_o[i]) map_o[i] = count_o;
            }
            else if (mark == IBoard::MARK_EMPTY)
            {
                if (!map_x[i]) map_x[i] = count_x;
                else if (count_x > map_x[i]) map_x[i] = count_x;

                if (!map_o[i]) map_o[i] = count_o;
                else if (count_o > map_o[i]) map_o[i] = count_o;

                count_x = 0;
                count_o = 0;
            }
        }
    }

    std::pair<int, int> max_x = getMaxOfMap(map_x);
    std::pair<int, int> max_o = getMaxOfMap(map_o);
    int winCondition = m_game->getMarksInRow();

    
    if (max_o.first == winCondition - 1) {
        pos.x = max_o.second;
        for (int i = lo_y; i < up_y; i++)
        {
            pos.y = i;
            auto mark = m_game->board()->mark(pos);
            if (mark == IBoard::MARK_EMPTY)
                return pos;
        }
    }

    if (max_x.first == winCondition - 1) {
        pos.x = max_x.second;
        for (int i = lo_y; i < up_y; i++)
        {
            pos.y = i;
            auto mark = m_game->board()->mark(pos);
            if (mark == IBoard::MARK_EMPTY)
                return pos;
        }
    }
    
    pos.x = -1;
    pos.y = -1;
    return pos;
}

std::pair<int, int> AIPlayer::getMaxOfMap(std::map<int, int > marksMap) const
{
    int max = 0, index = 0;
    for (std::map<int, int>::iterator it = marksMap.begin();
        it != marksMap.end(); ++it)
    {
        if (it->second > max)
        {
            max = it->second;
            index = it->first;
        }
    }
    return std::pair<int, int>{ max, index };
}
