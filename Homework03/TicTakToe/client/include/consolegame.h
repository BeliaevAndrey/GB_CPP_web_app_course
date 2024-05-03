#ifndef CONSOLEGAME_H
#define CONSOLEGAME_H

//---------------------------------------
#include <vector>
#include <utility>
#include <memory>   // added 2024.04.27

#include "player.h"
#include "board.h"
#include "game.h"

//=======================================
class ConsoleGame : public IGame
{
public:
    ConsoleGame() = default;
    ConsoleGame(const std::string& name,
        IBoard* board,
        int marksInRow);
    ~ConsoleGame() = default;

    virtual std::string name() const override { return m_name; }
    virtual bool setup(IBoard* board) override;
    virtual bool waitForPlayers(uint64_t timeout) override;
    virtual int  exec(/*add parameters*/) override;

protected:
    void renderBoard() const;
    int  calculateVictory();

private:
    std::string m_name;
    std::unique_ptr<IBoard> m_board;
    std::vector<std::unique_ptr<IPlayer>> m_players;
    int marksInRow;
};

#endif // CONSOLEGAME_H
