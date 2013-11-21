#include "statelesstooltipsingleton.hpp"

bool StatelessToolTipSingleton::addToolButton(std::string&& tooltipMessage, std::string&& icon, type_callback callback)
{
    Data d {tooltipMessage, icon, callback};
    instance().m_container.push_back(std::move(d));
    return true;
}
