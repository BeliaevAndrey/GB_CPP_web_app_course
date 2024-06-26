//--------------------------------
#include <string>
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
                new AIPlayer("Automatic one", this, m_ui)
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

            checker(pos, count_x, count_o);
            if (count_x == marksInRow || count_o == marksInRow) return true;
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

            checker(pos, count_x, count_o);
            if (count_x == marksInRow || count_o == marksInRow) return true;
        }
    }

    // LTR diagonals higher than main diagonal
    for (int row = ymin; row < ymax - marksInRow; row++)
    {
        count_x = 0;
        count_o = 0;
        for (int col = row; col < xmax; col++)
        {
            pos.x = col - row;
            pos.y = col;

            checker(pos, count_x, count_o);
            if (count_x == marksInRow || count_o == marksInRow) return true;
        }
    }

    // LTR diagonals lower than main diagonal

    for (int row = ymin + 1; row < ymax; row++)
    {
        count_x = 0;
        count_o = 0;
        for (int col = xmin; col < xmax - row; col++)
        {
            pos.x = row + col;
            pos.y = col;

            checker(pos, count_x, count_o);
            if (count_x == marksInRow || count_o == marksInRow) return true;
        }
    }
   
    // RTL diagonals higher than side diagonal

    for (int y = ymax - 1; y > ymin; y--)
    {
        count_x = 0;
        count_o = 0;

        int delta = 0;

        for (int k = xmin; k < xmax; k++)
        {
            pos.y = y - delta;
            pos.x = delta;
            ++delta;

            checker(pos, count_x, count_o);
            if (count_x == marksInRow || count_o == marksInRow)
            {
                return true;
            }

            if (y - delta <= ymin)
                break;
        }
    }
    
    // RTL diagonals lower than side diagonal

    for (int x = xmin; x < xmax; x++)
    {
        count_x = 0;
        count_o = 0;

        int delta = 0;

        for (int k = xmin; k < xmax - 1, x + k < xmax; k++)
        {
            pos.y = ymax - 1 - delta;
            pos.x = x + k;
            ++delta;
            checker(pos, count_x, count_o);
            if (count_x == marksInRow || count_o == marksInRow)
            {
                return true;
            }

        }
    }

    return false;
}

void ConsoleGame::checker(IBoard::PositionType pos, int& count_x, int& count_o)
{
    auto mark = m_board->mark(pos);

            switch (mark) {
            case IBoard::MARK_X:
            {
                count_x++;
                count_o = 0;
                break;
            }
            case IBoard::MARK_O:
            {
                count_o++;
                count_x = 0;
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
