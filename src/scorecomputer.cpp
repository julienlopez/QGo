#include "scorecomputer.hpp"

#include <goban.hpp>

#include <cassert>

#include <QDebug>

void ScoreComputer::computeScore(QGo::goban_sp goban)
{
    assert(!goban.get());

    qDebug() << "ScoreComputer::computeScore()";
    qDebug() << "taille du goban: " << goban->size();

    type_list_group groups = findWorms(goban);
}

ScoreComputer::type_list_group ScoreComputer::findWorms(QGo::goban_sp goban)
{
    type_list_group res;
    std::size_t size = goban->size()+1;
    type_set_point pointsLeft;
    for(std::size_t i = 0; i < size; i++)
        for(std::size_t j = 0; j < size; j++)
            pointsLeft.insert(Point(i, j));

    for(type_set_point::const_iterator i = pointsLeft.begin(); i != pointsLeft.end();)
    {
        QGo::Case c = (*goban)(i->x(), i->y());
        if(c ==QGo::EMPTY)
        {
            ++i;
            continue;
        }
        res.push_back(goban->computeGroup(i->x(), i->y()));
        //TODO retirer tous les points appartenants au groups de la liste des points restants
    }
    return res;
}
