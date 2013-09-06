#ifndef MARKLIBERTIES_HPP
#define MARKLIBERTIES_HPP

#include "crtp_state.hpp"

class MarkLiberties : public CRTP_State<MarkLiberties>
{
public:
    MarkLiberties() noexcept = default;
    virtual ~MarkLiberties() noexcept = default;

    virtual std::string statusBarMessage() const noexcept override;

    static std::string toolTipMessage() noexcept;
    static std::string icone() noexcept;

    virtual void leftClick(QGo::goban_sp goban, uint8_t x, uint8_t y) override;
};

#endif // MARKLIBERTIES_HPP
