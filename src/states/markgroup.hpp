#ifndef MARKGROUP_HPP
#define MARKGROUP_HPP

#include "crtp_state.hpp"

class MarkGroup : public CRTP_State<MarkGroup>
{
public:
    MarkGroup() noexcept = default;
    virtual ~MarkGroup() noexcept = default;

    virtual std::string statusBarMessage() const noexcept override;

    static std::string toolTipMessage() noexcept;
    static std::string icone() noexcept;

    virtual void leftClick(QGo::goban_sp goban, uint8_t x, uint8_t y) override;
};

#endif // MARKGROUP_HPP
