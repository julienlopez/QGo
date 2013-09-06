#ifndef IMAINWINDOW_HPP
#define IMAINWINDOW_HPP

#include <utils/noncopiable.hpp>
#include <point.hpp>

#include <string>
#include <list>

class iMainWindow : public utils::noncopiable
{
public:
    virtual void popUpInt(const std::string& title, const std::string& message, int value) =0;

    virtual void markGroup(const std::list<Point>& points) =0;

    static iMainWindow& instance();

protected:
    iMainWindow() = default;
    ~iMainWindow() = default;

    static void setInstance(iMainWindow* instance);

private:
    static iMainWindow* s_instance;
};

#endif // IMAINWINDOW_HPP
