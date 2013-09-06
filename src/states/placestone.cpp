#include "placestone.hpp"
#include "statefactory.hpp"
#include "goban.hpp"

std::string PlaceStone::statusBarMessage() const noexcept
{
    return "Click on the board to place a stone";
}

std::string PlaceStone::toolTipMessage() noexcept
{
    return "Place a stone";
}

std::string PlaceStone::icone() noexcept
{
    return "place_stone.png";
}

void PlaceStone::leftClick(QGo::goban_sp goban, uint8_t x, uint8_t y)
{
    static Goban::Case color = Goban::BLACK;
    goban->placeStone(x, y, color);
    if(color == Goban::BLACK) color = Goban::WHITE;
    else color = Goban::BLACK;
}
