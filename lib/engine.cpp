#include "engine.hpp"
#include "goban.hpp"

#include <boost/weak_ptr.hpp>

Engine& Engine::instance()
{
    static Engine instance;
    return instance;
}

QGo::goban_wp Engine::goban()
{
    return m_goban;
}

uint8_t Engine::size() const
{
    return m_size;
}

void Engine::setSize(uint8_t s)
{
    m_size = s;
}

Engine::Engine(): m_size(19)
{
    init();
}

void Engine::init()
{
    m_goban.reset(new Goban(m_size));
}
