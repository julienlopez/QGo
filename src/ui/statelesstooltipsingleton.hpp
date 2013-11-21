#ifndef STATELESSTOOLTIPSINGLETON_HPP
#define STATELESSTOOLTIPSINGLETON_HPP

#include <utils/singleton.hpp>

#include <list>
#include <functional>

class StatelessToolTipSingleton : utils::singleton<StatelessToolTipSingleton>
{
    friend class utils::singleton<StatelessToolTipSingleton>;
public:
    using type_callback = std::function<void()>;

private:
    struct Data
    {
        std::string tooltipMessage;
        std::string icon;
        type_callback callback;
    };

    using type_container = std::list<Data>;

public:
    static bool addToolButton(std::string&& tooltipMessage, std::string&& icon, type_callback callback);

    template<class F> static void for_each(F func)
    {
        for(const auto& t : instance().m_container)
        {
            func(t.tooltipMessage, t.icon, t.callback);
        }
    }

protected:
    StatelessToolTipSingleton() = default;

private:
    type_container m_container;
};

#endif // STATELESSTOOLTIPSINGLETON_HPP
