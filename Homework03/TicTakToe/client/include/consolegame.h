#ifndef CONSOLEGAME_H
#define CONSOLEGAME_H

//---------------------------------------
#include <vector>
#include <utility>
#include <memory>

#include "player.h"
#include "board.h"
#include "game.h"

#include "uicommon.h"

//=======================================
class ConsoleGame : public IGame
{
public:
    ConsoleGame() = default;
 
    ConsoleGame(const std::string& name,
        IBoard* board,
        ICommonUI* _ui,
        int marksInRow,
        int _playersAmt);

    ~ConsoleGame() = default;

    virtual std::string name() const override { return m_name; }
    virtual bool setup(IBoard* board) override;
    virtual bool waitForPlayers(uint64_t timeoutm) override;
    virtual int  exec(/*add parameters*/) override;

    // additions
    virtual IBoard* board() const override;
    virtual int getMarksInRow() const override;

protected:
    // void renderBoard() const; // moved to UI
    int  calculateVictory();
    void  checker(IBoard::PositionType, int& , int& );

private:
    std::string m_name;
    std::unique_ptr<IBoard> m_board;
    std::vector<std::unique_ptr<IPlayer>> m_players;
    
    // additions
    int marksInRow;
    int playersAmt;
    ICommonUI* m_ui;


};

#endif // CONSOLEGAME_H
