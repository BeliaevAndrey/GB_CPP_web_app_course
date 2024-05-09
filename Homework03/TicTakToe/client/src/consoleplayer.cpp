#include "consoleplayer.h"

//---------------------------------
#include <optional>
#include <iostream>

//=================================
std::string ConsolePlayer::name() const
{ return m_name;}

std::optional<IBoard::PositionType> ConsolePlayer::getMove(uint64_t /*timeout = -1*/) const
{
    IBoard::PositionType pos;
    std::string prompt = "player, " + name() + ", enter your move:";
    m_ui->readMove(pos, prompt);

    return pos;
}
