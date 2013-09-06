#include "markliberties.hpp"
#include "statefactory.hpp"
#include <goban.hpp>
#include <ui/imainwindow.hpp>

std::string MarkLiberties::statusBarMessage() const noexcept
{
    return "Click on the board select the group of which you want to mark the liberties";
}

std::string MarkLiberties::toolTipMessage() noexcept
{
    return "Mark the liberties of a group";
}

std::string MarkLiberties::icone() noexcept
{
    return "mark_liberties.png";
}

void MarkLiberties::leftClick(QGo::goban_sp goban, uint8_t x, uint8_t y)
{
    Goban::type_set_point group = goban->computeLiberties(x, y);
    if(group.empty()) return;
    std::list<Point> lst(group.begin(), group.end());
    iMainWindow::instance().markGroup(lst);
}
