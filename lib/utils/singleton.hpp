#ifndef SINGLETON_HPP
#define SINGLETON_HPP

#include <utils/noncopiable.hpp>

BEGIN_NAMESPACE_UTILS

template<class T> class singleton : public noncopiable {
public:
    static T& instance() {
        static T i;
        return i;
    }

protected:
    singleton() {}
};

END_NAMESPACE_UTILS

#endif // SINGLETON_HPP
