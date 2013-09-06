#include "imainwindow.hpp"

#include <cassert>

iMainWindow* iMainWindow::s_instance = 0;

iMainWindow& iMainWindow::instance()
{
    assert(s_instance);
    return *s_instance;
}

void iMainWindow::setInstance(iMainWindow* instance)
{
    assert(!s_instance && instance);
    s_instance = instance;
}

