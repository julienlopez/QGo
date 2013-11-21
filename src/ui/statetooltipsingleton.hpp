#ifndef STATETOOLTIPSINGLETON_HPP
#define STATETOOLTIPSINGLETON_HPP

#include <utils/singleton.hpp>
#include <map>

class StateToolTipSingleton : utils::singleton<StateToolTipSingleton>
{
    friend class utils::singleton<StateToolTipSingleton>;
public:
    typedef std::map<std::size_t, std::pair<std::string, std::string>> type_map;

    static void addToolButton(type_map::value_type::first_type idState, type_map::value_type::second_type::first_type&& tooltipMessage, type_map::value_type::second_type::second_type&& icon);

    template<class F> static void for_each(F func)
    {
        for(const type_map::value_type& t : instance().m_map)
        {
            func(t.first, t.second.first, t.second.second);
        }
    }

protected:
    StateToolTipSingleton() = default;

private:
    type_map m_map;
};

#endif // TOOLTIPSINGLETON_HPP
