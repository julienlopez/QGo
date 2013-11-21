#include "scorecomputer.hpp"

#include <engine.hpp>
#include <ui/statelesstooltipsingleton.hpp>

namespace
{

void computeScore()
{
    QGo::goban_wp g = Engine::instance().goban();
    QGo::goban_sp goban = g.lock();
    if(!goban.get()) return;
    ScoreComputer::computeScore(goban);
}

bool registered = StatelessToolTipSingleton::addToolButton("", "", &computeScore);

}
