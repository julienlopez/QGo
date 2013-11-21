#include "scorecomputer.hpp"

#include <ui/statelesstooltipsingleton.hpp>

#include <engine.hpp>
#include <goban.hpp>

#include <QDebug>

bool registered = StatelessToolTipSingleton::addToolButton("", "", &ScoreComputer::computeScore);

void ScoreComputer::computeScore()
{
    QGo::goban_wp g = Engine::instance().goban();
    QGo::goban_sp goban = g.lock();
    if(!goban.get()) return;

    qDebug() << "ScoreComputer::computeScore()";
    qDebug() << "taille du goban: " << goban->size();
    std::size_t size = goban->size()+1;
//    std::vector<Point> pointsLeft(pow(goban->size()+1, 2));
}
