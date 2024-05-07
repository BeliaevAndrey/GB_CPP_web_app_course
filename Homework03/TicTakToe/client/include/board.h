#ifndef BOARD_H
#define BOARD_H

//----------------------------------
#include <utility>

//==================================
class IBoard
{
private:
    bool drawBoard;

public:
    struct PositionType
    {
        typedef unsigned int Dimension;
        Dimension x = 0;
        Dimension y = 0;
    };

    enum Mark : unsigned char
    {
        MARK_UNKNOWN = 0xff
        , MARK_EMPTY = 0
        , MARK_O
        , MARK_X
    };

    virtual ~IBoard() = default;

    virtual std::pair<PositionType, PositionType> dimension() const { return std::pair<PositionType, PositionType>{}; }
    virtual Mark mark(const PositionType& pos) const { return MARK_UNKNOWN; }
    virtual bool setMark(const PositionType& pos, const Mark& mark) { return false; }

    // additions
    virtual void drawCheck() {};
    virtual bool isDraw() const { return drawBoard; };
};

#endif // BOARD_H
