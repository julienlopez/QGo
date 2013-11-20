#ifndef CRTP_SYSTEM_HPP
#define CRTP_SYSTEM_HPP

#include "statefactory.hpp"

template<class T> class CRTP_State : public State
{
protected:
    template<typename... Args> CRTP_State(Args&&... args) noexcept : State(std::forward<Args>(args)...)
    {}

    typedef StateFactory::type_identifier type_key;

    virtual type_key key() const
    {
        return s_key;
    }

public:
    static const type_key s_key;
};

template<class T> const typename CRTP_State<T>::type_key CRTP_State<T>::s_key = StateFactory::registerProduct([](){ return new T(); }, T::toolTipMessage(), T::icone());

#endif // CRTP_SYSTEM_HPP
