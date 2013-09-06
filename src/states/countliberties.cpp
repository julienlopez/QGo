#include "countliberties.hpp"
#include "statefactory.hpp"
#include <goban.hpp>
#include <ui/imainwindow.hpp>

std::string CountLiberties::statusBarMessage() const noexcept
{
    return "Click on the board select the group of which you want to count the liberties";
}

std::string CountLiberties::toolTipMessage() noexcept
{
    return "Count the liberties of a group";
}

std::string CountLiberties::icone() noexcept
{
    return "count_liberties.png";
}

void CountLiberties::leftClick(QGo::goban_sp goban, uint8_t x, uint8_t y)
{
    Goban::type_set_point group = goban->computeLiberties(x, y);
    iMainWindow::instance().popUpInt("Count liberties", "number of liberties: ", group.size());
}
