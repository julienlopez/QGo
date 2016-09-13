#ifndef POINT_HPP
#define POINT_HPP

#include "globals.hpp"

class Point
{
public:
    Point(uint8_t x_, uint8_t y_);

    uint8_t x() const;
    uint8_t y() const;

    void setX(uint8_t x_);
    void setY(uint8_t y_);

    bool operator==(const Point& p) const;
    bool operator!=(const Point& p) const;
    bool operator<(const Point& p) const;

private:
    uint8_t m_x;
    uint8_t m_y;
};

#endif // POINT_HPP
