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
    for (auto row = ymin; row < ymax; row++)
    {
        count_x = 0;
        count_o = 0;
        pos.y = row;  // set position -- row
        for (auto col = xmin; col < xmax; col++)
        {
            pos.x = col;      // set position -- column
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
    for (auto col = xmin; col < xmax; col++)
    {
        count_x = 0;
        count_o = 0;
        pos.x = col;  // set position -- column
        for (auto row = ymin; row < ymax; row++)
        {
            pos.y = row;      // set position -- row
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

  
    // LTR diagonals higher than main diagonal
    for (int row = ymin; row < ymax - marksInRow; row++)
    {
        count_x = 0;
        count_o = 0;
        for (int col = row; col < xmax; col++)
        {
            pos.x = col - row;
            pos.y = col;
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

    // LTR diagonals lower than main diagonal

    for (int row = ymin + 1; row < ymax; row++)
    {
        count_x = 0;
        count_o = 0;
        for (int col = xmin; col < xmax - row; col++)
        {
            pos.x = row + col;
            pos.y = col;
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

    // RTL diagonals lower than main diagonal

    for (int row = ymin; row < ymax; row++)
    {
        count_x = 0;
        count_o = 0;
        int  i = 0;

        for (int col = xmax - 1; col > row - 1; col--)
        {
            pos.x = row + i;
            i++;
            pos.y = col;
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

            // i++;
        }
    }

    // RTL diagonals higher than main diagonal
    for (int row = ymax - 2; row > ymin - 1; row--)
    {
        count_x = 0;
        count_o = 0;
        int i = 0;

        for (int col = xmin; col < row + 1; col++)
        {
            pos.x = row - i;
            i++;
            pos.y = col;

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

