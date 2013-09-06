#ifndef COUNTLIBERTIES_HPP
#define COUNTLIBERTIES_HPP

#include "crtp_state.hpp"

class CountLiberties : public CRTP_State<CountLiberties>
{
public:
    CountLiberties() noexcept = default;
    virtual ~CountLiberties() noexcept = default;

    virtual std::string statusBarMessage() const noexcept override;

    static std::string toolTipMessage() noexcept;
    static std::string icone() noexcept;

    virtual void leftClick(QGo::goban_sp goban, uint8_t x, uint8_t y) override;
};

#endif // COUNTLIBERTIES_HPP
