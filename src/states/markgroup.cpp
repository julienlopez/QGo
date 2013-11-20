#include "markgroup.hpp"
#include <goban.hpp>
#include <ui/imainwindow.hpp>

std::string MarkGroup::statusBarMessage() const noexcept
{
    return "Click on the board to select the group you want to mark";
}

std::string MarkGroup::toolTipMessage() noexcept
{
    return "Mark a group";
}

std::string MarkGroup::icone() noexcept
{
    return "mark_group.png";
}

void MarkGroup::leftClick(QGo::goban_sp goban, uint8_t x, uint8_t y)
{
    Goban::type_set_point group = goban->computeGroup(x, y);
    if(group.empty()) return;
    std::list<Point> lst(group.begin(), group.end());
    iMainWindow::instance().markGroup(lst);
}
