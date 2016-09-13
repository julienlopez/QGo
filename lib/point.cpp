#include "point.hpp"

Point::Point(uint8_t x_, uint8_t y_): m_x(x_), m_y(y_)
{}

uint8_t Point::x() const
{
    return m_x;
}

uint8_t Point::y() const
{
    return m_y;
}

void Point::setX(uint8_t x_)
{
    m_x = x_;
}

void Point::setY(uint8_t y_)
{
    m_y = y_;
}

bool Point::operator==(const Point& p) const
{
    return m_y == p.m_y && m_x == p.m_x;
}

bool Point::operator!=(const Point& p) const
{
    return m_y != p.m_y || m_x != p.m_x;
}

bool Point::operator<(const Point& p) const
{
    if(m_x == p.m_x) return m_y < p.m_y;
    return m_x < p.m_x;
}
