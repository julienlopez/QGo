#ifndef GOBANMAKINGHELPER_HPP
#define GOBANMAKINGHELPER_HPP

#include <globals.hpp>

#include <string>

class GobanMakingHelper
{
public:
    GobanMakingHelper() = delete;

    static void buildGoban(QGo::goban_sp goban, uint8_t size, const QGo::type_list_point& blackMoves, const QGo::type_list_point& whiteMoves);

private:
    static std::string encodeInt8(uint8_t i);

    static std::string makeMove(char player, uint8_t x, uint8_t y);
};

#endif // GOBANMAKINGHELPER_HPP
