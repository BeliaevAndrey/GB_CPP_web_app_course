//--------------------------------
#include <string>
#include <iostream>
#include "simpleboard.h"
#include "consoleplayer.h"

#include "consolegame.h"

//================================
ConsoleGame::ConsoleGame(const std::string& name, IBoard* board,
    int inMarksInRow)
    :m_name(name), marksInRow(inMarksInRow)
{
    setup(board);
}

bool ConsoleGame::setup(IBoard* board)
{
    if (m_players.empty())
        m_board.reset(board);
    return true;
}

bool ConsoleGame::waitForPlayers(uint64_t /*timeout*/)
{
    while (m_players.size() < 2)
    {
        std::cout << "Enter name of players " << std::to_string(m_players.size() + 1) << std::endl;

        std::string name;
        std::cin >> name;
        if (name.empty())
            continue;

        m_players.emplace_back(new ConsolePlayer(name));
    }

    return true;
}

void ConsoleGame::renderBoard() const
{
    auto dimensions = m_board->dimension();
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
            auto mark = m_board->mark(pos);
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


int  ConsoleGame::calculateVictory()
{
    auto dimensions = m_board->dimension();
    const auto& xmin = dimensions.first.x;
    const auto& ymin = dimensions.first.y;
    const auto& xmax = dimensions.second.x;
    const auto& ymax = dimensions.second.y;

    int count_x = 0;           // marks 'x' counter
    int count_o = 0;           // marks 'o' counter

    IBoard::PositionType pos; // position variable

    // check rows win condition
    for (auto i = ymin; i < ymax; i++)
    {
        count_x = 0;
        count_o = 0;
        pos.y = i;  // set position -- row
        for (auto j = xmin; j < xmax; j++)
        {
            pos.x = j;      // set position -- column
            auto mark = m_board->mark(pos); // get a mark from position
            switch (mark) {
            case IBoard::MARK_X:
            {
                count_x++;
                count_o = 0;
                if (count_x == marksInRow) return true;
                break;
            }

            case IBoard::MARK_O:
            {
                count_o++;
                count_x = 0;
                if (count_o == marksInRow) return true;
                break;
            }

            case IBoard::MARK_EMPTY:
            {
                count_x = 0;
                count_o = 0;
            }

            default: break;
            }
        }

    }


    // check columns win condition
    for (auto i = xmin; i < xmax; i++)
    {
        count_x = 0;
        count_o = 0;
        pos.x = i;  // set position -- row
        for (auto j = ymin; j < ymax; j++)
        {
            pos.y = j;      // set position -- column
            auto mark = m_board->mark(pos); // get a mark from position
            switch (mark) {
            case IBoard::MARK_X:
            {
                count_x++;
                count_o = 0;
                if (count_x == marksInRow) return true;
                break;
            }

            case IBoard::MARK_O:
            {
                count_o++;
                count_x = 0;
                if (count_o == marksInRow) return true;
                break;
            }

            case IBoard::MARK_EMPTY:
            {
                count_x = 0;
                count_o = 0;
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
        pos.x = i;
        pos.y = i;
        auto mark = m_board->mark(pos);
        switch (mark) {
        case IBoard::MARK_X:
        {
            count_x++;
            count_o = 0;
            if (count_x == marksInRow) return true;
            break;
        }

        case IBoard::MARK_O:
        {
            count_o++;
            count_x = 0;
            if (count_o == marksInRow) return true;
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
        pos.x = xmax - i - 1;
        pos.y = i;
        auto mark = m_board->mark(pos);
        switch (mark) {
        case IBoard::MARK_X:
        {
            count_x++;
            count_o = 0;
            if (count_x == marksInRow) return true;
            break;
        }
        case IBoard::MARK_O:
        {
            count_o++;
            count_x = 0;
            if (count_o == marksInRow) return true;
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


    return false;
}


int  ConsoleGame::exec(/*add parameters*/)
{
    int iplayer = 0;
    while (true)
    {
        renderBoard();

        auto& player = m_players[iplayer];
        bool moveAccepted = false;
        while (!moveAccepted)
        {

            auto move = player->getMove();

            if (!move) return -1;

            // check coordinates are inside board
            if (move.value().x < m_board->dimension().first.x ||
                move.value().y < m_board->dimension().first.y ||
                move.value().x >= m_board->dimension().second.x ||
                move.value().y >= m_board->dimension().second.y)
                continue;

            auto currentMark = m_board->mark(move.value());

            if (currentMark == IBoard::MARK_EMPTY)
                moveAccepted = m_board->setMark(move.value(), iplayer == 0 ? IBoard::MARK_X : IBoard::MARK_O);
        }

        //calculate victory function
        if (calculateVictory() > 0)
        {
            renderBoard();

            std::cout << "player "
                << std::to_string(iplayer + 1) << " -- "
                << m_players[iplayer]->name()
                << " -- wins! Congratulations!"
                << std::endl;

            return iplayer;
        }

        iplayer = (iplayer + 1) % 2;    // switch players
    }
    return -1;
}

//[7]

