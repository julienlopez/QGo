#include "statetooltipsingleton.hpp"

#include <cassert>

void StateToolTipSingleton::addToolButton(std::size_t idState, std::string&& tooltipMessage, std::string&& icon)
{
    auto res = instance().m_map.insert(make_pair(idState, make_pair(tooltipMessage, icon)));
    assert(res.second);
}
