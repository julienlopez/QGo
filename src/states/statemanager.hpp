#ifndef STATEMANAGER_HPP
#define STATEMANAGER_HPP

#include <utils/singleton.hpp>

#include "state.hpp"

#include <memory>
#include <stack>

#include <boost/signals2.hpp>

class StateManager : protected utils::singleton<StateManager>
{
    friend class utils::singleton<StateManager>;
public:
    typedef std::unique_ptr<State> state_up;
    typedef std::stack<state_up> state_stack;
    typedef boost::signals2::signal<void(const std::string&)> type_signal_string;

    static void pop();
    static void push(state_up&& state);

    static type_signal_string& changeStatusBarMessage();

    static const state_up& currentState();

private:
    StateManager() = default;

    state_stack m_stack;
    type_signal_string m_changeStatusBarMessage;

    void activateTop();
};

#endif // STATEMANAGER_HPP
