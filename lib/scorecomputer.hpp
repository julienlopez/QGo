#ifndef SCORECOMPUTER_HPP
#define SCORECOMPUTER_HPP

#include <utils/noninstanciable.hpp>

#include <globals.hpp>

class ScoreComputer : utils::noninstanciable
{
public:
    static void computeScore(QGo::goban_sp);

    using type_set_point = QGo::type_set_point;
    using type_list_group = std::list<type_set_point>;

    static type_list_group findWorms(QGo::goban_sp goban);
};

#endif // SCORECOMPUTER_HPP
