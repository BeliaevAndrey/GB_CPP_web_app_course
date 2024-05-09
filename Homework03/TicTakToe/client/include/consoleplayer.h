#ifndef CONSOLEPLAYER_H
#define CONSOLEPLAYER_H

//----------------------------------
#include <string>
#include <optional>

#include "board.h"
#include "player.h"

#include "uicommon.h"

//==================================
class ConsolePlayer : public IPlayer
{
    public:
        ConsolePlayer() = default;
        
        ConsolePlayer(const std::string& name, 
        ICommonUI* _ui) : m_name(name), m_ui(_ui) {}
        
        ConsolePlayer(const std::string& name) : m_name(name) {}
        
        ~ConsolePlayer() = default;

        virtual std::string name() const override;
        virtual std::optional<IBoard::PositionType> getMove(uint64_t /*timeout = -1*/) const override;

    private:
        std::string m_name;
        ICommonUI* m_ui;

};

#endif // CONSOLEPLAYER_H
