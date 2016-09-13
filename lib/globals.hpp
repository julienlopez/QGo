#ifndef GLOBALS_HPP
#define GLOBALS_HPP

#include <cinttypes>

#include <memory>
#include <list>
#include <set>

typedef signed char int8_t;

class Goban;
class Point;

namespace QGo
{
    typedef std::shared_ptr<Goban> goban_sp;
    typedef std::weak_ptr<Goban> goban_wp;

    using type_list_point = std::list<Point>;

    using type_set_point = std::set<Point>;

    enum Case {EMPTY = 0, BLACK, WHITE};
}

#endif // GLOBALS_HPP
