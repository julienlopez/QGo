#ifndef GLOBALS_HPP
#define GLOBALS_HPP

#include <inttypes.h>

#include <memory>
#include <list>

typedef signed char 	int8_t;
//typedef unsigned char 	uint8_t;
//typedef signed int 	int16_t;
//typedef unsigned int 	uint16_t;
//typedef signed long int 	int32_t;
//typedef unsigned long int 	uint32_t;
//typedef signed long long int 	int64_t;
//typedef unsigned long long int 	uint64_t;

class Goban;
class Point;

namespace QGo
{
    typedef std::shared_ptr<Goban> goban_sp;
    typedef std::weak_ptr<Goban> goban_wp;

    typedef std::list<Point> type_list_point;

    enum Case {EMPTY = 0, BLACK, WHITE};
}

#endif // GLOBALS_HPP
