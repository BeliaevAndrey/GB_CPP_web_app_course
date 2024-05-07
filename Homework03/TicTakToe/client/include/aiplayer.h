#ifndef AIPLAYER_H
#define AIPLAYER_H

#include <string>
#include <optional>

#include "player.h"

class AIPlayer : public IPlayer
{
public:
    AIPlayer() = default;
    AIPlayer(const std::string& name, IBoard* board, int marksInRow) :
        m_name(name), m_board(board), m_marksInRow(marksInRow) {}
    ~AIPlayer() = default;

    virtual std::string name() const override;
    virtual std::optional<IBoard::PositionType> getMove(uint64_t /*timeout = -1*/) const override;

    IBoard::PositionType calculateMove();

private:
    std::string m_name;     // todo: name may be const (case user vs AI only; not AI vs AI)
    IBoard* m_board;
    const int m_marksInRow;
};

#endif // AIPLAYER_H