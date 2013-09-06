#include "statetoolbaraction.hpp"
#include <states/statefactory.hpp>
#include <states/statemanager.hpp>

#include <cassert>

StateToolBarAction::StateToolBarAction(std::size_t stateId, const QIcon &icon, const QString &title, QObject *parent) :
    QAction(icon, title, parent), m_stateId(stateId)
{
    connect(this, SIGNAL(triggered()), this, SLOT(onClick()));
    setCheckable(true);
}

void StateToolBarAction::onClick()
{
    StateManager::pop();
    std::unique_ptr<State> state(StateFactory::create(m_stateId));
    assert(state);
    StateManager::push(std::move(state));
}
