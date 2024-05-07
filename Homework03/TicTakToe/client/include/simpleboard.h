#ifndef SIMPLEBOARD_H
#define SIMPLEBOARD_H

//------------------------------
#include <utility>
#include <exception>
#include <stdexcept>

#include "board.h"

//==============================
//--------------------------------------------
// template<std::size_t N>
class SimpleBoard : public IBoard
{
public:
    // SimpleBoard() = default;
    SimpleBoard(const int bSize) : N((std::size_t)bSize)
    {
        m_marks = new Mark * [N];
        for (int i = 0; i < N; i++)
        {
            m_marks[i] = new Mark[N];
            for (int j = 0; j < N; j++)
            {
                m_marks[i][j] = IBoard::MARK_EMPTY;
            }

        }
    };
    SimpleBoard& operator=(const SimpleBoard& other) = delete;
    SimpleBoard(const SimpleBoard& other) = delete;
    SimpleBoard(SimpleBoard& other) = delete;
    ~SimpleBoard() = default;

    virtual std::pair<PositionType, PositionType> dimension() const override
    {
        return std::make_pair(PositionType{}, m_size);
    }

    virtual Mark mark(const PositionType& pos) const override
    {
        if (pos.x < m_size.x && pos.y < m_size.y)
            return m_marks[pos.x][pos.y];

        throw std::invalid_argument("Invalid position");
        return MARK_UNKNOWN;
    }

    virtual bool setMark(const PositionType& pos, const Mark& mark) override
    {
        if (pos.x < m_size.x && pos.y < m_size.y) {
            m_marks[pos.x][pos.y] = mark;
            drawCheck();
            return true;
        }
        return false;
    }

    // Is board filled up
    virtual void drawCheck() override {
        int marked = 0;
        for (int i=0; i < N; i++)
        {
            for (int j=0; j < N; j++)
            {
                if (m_marks[j][i] != IBoard::MARK_EMPTY)
                marked++;
                if (marked == N * N) drawBoard = true;
            }
        }
    }

    virtual bool isDraw() const override {
        return drawBoard;
    }

private:
    const std::size_t N;
    PositionType m_size = { static_cast<unsigned int>(N),
                            static_cast<unsigned int>(N) };
    // Mark m_marks[N][N] = { IBoard::MARK_EMPTY };
    Mark** m_marks = nullptr;
    bool drawBoard = false;
};

#endif // SIMPLEBOARD_H
