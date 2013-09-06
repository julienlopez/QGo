#ifndef STATE_HPP
#define STATE_HPP

#include <globals.hpp>

#include <string>

class State
{
public:
    virtual ~State() noexcept = default;

    virtual std::string statusBarMessage() const noexcept =0;

    virtual void leftClick(QGo::goban_sp goban, uint8_t x, uint8_t y) = 0;

protected:
    State() noexcept = default;
};

#endif // STATE_HPP
