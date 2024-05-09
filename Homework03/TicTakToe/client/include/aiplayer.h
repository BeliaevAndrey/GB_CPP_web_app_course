#ifndef AIPLAYER_H
#define AIPLAYER_H

#include <string>
#include <optional>
#include <map>

#include "player.h"
#include "game.h"
#include "uicommon.h"

class AIPlayer : public IPlayer
{
public:
    AIPlayer() = default;
    AIPlayer(const std::string& name, IGame* game, ICommonUI* _ui) :
        m_name(name), m_game(game), m_ui(_ui)
    {};
    ~AIPlayer() = default;

    virtual std::string name() const override;
    virtual std::optional<IBoard::PositionType> getMove(uint64_t /*timeout = -1*/) const override;

    // for inner checks
    IBoard::PositionType checkRows(int, int, int, int) const;
    
    IBoard::PositionType checkCols(int, int, int, int) const;

    std::pair<int, int> getMaxOfMap(std::map<int, int>) const;

private:
    std::string m_name; 
    IGame* m_game;
    ICommonUI* m_ui;
};

#endif // AIPLAYER_H