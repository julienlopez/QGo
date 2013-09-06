#include "statemanager.hpp"

void StateManager::pop()
{
    StateManager& sm = StateManager::instance();
    if(sm.m_stack.empty()) return;
    sm.m_stack.pop();
    if(!sm.m_stack.empty()) sm.activateTop();
}

void StateManager::push(state_up&& state)
{
    instance().m_stack.push(std::move(state));
    instance().activateTop();
}

void StateManager::activateTop()
{
    m_changeStatusBarMessage(m_stack.top()->statusBarMessage());
}

StateManager::type_signal_string& StateManager::changeStatusBarMessage()
{
    return instance().m_changeStatusBarMessage;
}

const StateManager::state_up& StateManager::currentState()
{
    StateManager& sm = StateManager::instance();
    if(sm.m_stack.empty()) throw std::logic_error("State stack is empty!");
    return sm.m_stack.top();
}
