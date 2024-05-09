//--------------------------------
#include <string>
#include <iostream>
#include <memory>

#include "simpleboard.h"
#include "consoleplayer.h"

#include "aiplayer.h"   // computer player

#include "consolegame.h"

//================================
ConsoleGame::ConsoleGame(const std::string& name, IBoard* board,
    ICommonUI* _ui, int _marksInRow, int _playersAmt)
    :m_name(name), marksInRow(_marksInRow), playersAmt(_playersAmt), m_ui(_ui)
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
        std::string name;
        m_ui->readString(name, "name of player");

        if (name.empty())
            continue;

        m_players.emplace_back(new ConsolePlayer(name, m_ui));

        if (playersAmt == 1)
        {
            m_players.emplace_back(
                new AIPlayer("Automatic one", this)
            );
        }
    }

    return true;
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
                break;
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
                break;
            }

            default: break;
            }
        }
    }

    // check left to right diagonal
    for (int col = xmin; col < xmax; col++) {
        count_x = 0;
        count_o = 0;
        for (int i = xmin; i < xmax; i++)
        {
            pos.x = i + (i + col < xmax ? col : 0);
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
    }

    // check right to left diagonal
    for (int col = xmin; col < xmax; col++)
    {
        for (int i = xmin; i < xmax; i++)
        {
            pos.x = xmax - i - 1;
            pos.x = pos.x + (pos.x + col < xmax ? col : 0);
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
    }


    return false;
}


int  ConsoleGame::exec(/*add parameters*/)
{
    int iplayer = 0;
    while (true)
    {
        m_ui->renderBoard(this);

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

        // Check draw game 
        if (m_board->isDraw())
        {
            m_ui->renderBoard(this);
            m_ui->printMsg("DRAW! Nobody wins");

            return -1;
        }

        //calculate victory function
        else if (calculateVictory() > 0)
        {
            m_ui->renderBoard(this);

            std::string congratulations = "player " +
                std::to_string(iplayer + 1) + " " +
                m_players[iplayer]->name() +
                " -- wins! Congratulations!";

            m_ui->printMsg(congratulations);

            return iplayer;
        }

        iplayer = (iplayer + 1) % 2;    // switch players
    }
    return -1;
}

//[7]

// additions
IBoard* ConsoleGame::board() const
{
    return m_board.get();
}

int ConsoleGame::getMarksInRow() const { return marksInRow; }

