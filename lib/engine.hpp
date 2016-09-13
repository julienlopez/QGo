#ifndef ENGINE_HPP
#define ENGINE_HPP

#include "globals.hpp"

class Engine
{
public:

    static Engine& instance();

    QGo::goban_wp goban();

    uint8_t size() const;
    void setSize(uint8_t);

private:
    Engine();

    void init();

    uint8_t m_size;
    QGo::goban_sp m_goban;
};

#endif // ENGINE_HPP
