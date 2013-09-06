#ifndef PLACESTONE_HPP
#define PLACESTONE_HPP

#include "crtp_state.hpp"

class PlaceStone : public CRTP_State<PlaceStone>
{
public:
    PlaceStone() noexcept = default;
    virtual ~PlaceStone() noexcept = default;

    virtual std::string statusBarMessage() const noexcept override;

    static std::string toolTipMessage() noexcept;
    static std::string icone() noexcept;

    virtual void leftClick(QGo::goban_sp goban, uint8_t x, uint8_t y) override;
};

#endif // PLACESTONE_HPP
