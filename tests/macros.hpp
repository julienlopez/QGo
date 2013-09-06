#ifndef TESTMACROS_HPP
#define TESTMACROS_HPP

#include <QTest>

#define EXPECT_THROW( func, exceptionClass ) \
{ \
    bool caught = false; \
    try { \
        (func); \
    } \
    catch ( exceptionClass& e ) { \
        if ( typeid( e ) != typeid( exceptionClass ) ) { \
            QWARN("Derived exception caught"); \
        } \
        caught = true; \
    } catch (...) {} \
    if(!caught) QFAIL("Nothing thrown"); \
};

#define EXPECT_NOTHROW(func) \
{ \
    try { \
        (func); \
    } \
    catch(...) \
    { \
        QFAIL("An exception was thrown");\
    } \
};

#endif // TESTMACROS_HPP
