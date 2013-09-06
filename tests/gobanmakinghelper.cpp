#include "gobanmakinghelper.hpp"

#include <game.hpp>
#include <sgfreader.hpp>

#include <cassert>

void GobanMakingHelper::buildGoban(QGo::goban_sp goban, uint8_t size, const QGo::type_list_point& blackMoves, const QGo::type_list_point& whiteMoves)
{
    std::list<std::string> lines = {{"SZ[" + std::to_string(size) + "]"}};
    for(const Point& p : blackMoves)
        lines.push_back(makeMove('b', p.x(), p.y()));
    for(const Point& p : whiteMoves)
        lines.push_back(makeMove('w', p.x(), p.y()));
    Game g = SGFReader::parse(lines);
    g.loadMovesOnto(goban);
}

std::string GobanMakingHelper::encodeInt8(uint8_t i)
{
    if(i < 27) return std::string(1, 'a' + i);
    return std::string(1, 'A'+(i-27));
}

std::string GobanMakingHelper::makeMove(char player, uint8_t x, uint8_t y)
{
    assert(player == 'b' || player == 'B' || player == 'w' || player == 'W');
    return ";" + std::string(1, toupper(player)) + "[" + encodeInt8(x) + encodeInt8(y) + "]";
}
