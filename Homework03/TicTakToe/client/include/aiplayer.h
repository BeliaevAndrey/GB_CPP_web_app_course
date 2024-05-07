#ifndef AIPLAYER_H
#define AIPLAYER_H

#include <string>
#include <optional>
#include <iostream>

#include "player.h"
#include "game.h"

class AIPlayer : public IPlayer
{
public:
    AIPlayer() = default;
    AIPlayer(const std::string& name, IGame* game) :
        m_name(name), m_game(game)
    {};
    ~AIPlayer() = default;

    virtual std::string name() const override;
    virtual std::optional<IBoard::PositionType> getMove(uint64_t /*timeout = -1*/) const override;

private:
    std::string m_name;     // todo: name may be const (in case user vs AI only; not AI vs AI)
    IGame* m_game;
};

#endif // AIPLAYER_H