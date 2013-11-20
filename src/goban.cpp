#include "goban.hpp"

#include <algorithm>
#include <cassert>

Goban::Goban(uint8_t size_): m_size(size_), m_array(pow(size_+1, 2), QGo::EMPTY)
{}

void Goban::resize(uint8_t newSize)
{
    m_size = newSize;
    m_array.resize(newSize*newSize);
    std::fill(m_array.begin(), m_array.end(), QGo::EMPTY);
}

uint8_t Goban::size() const
{
    return m_size;
}

void Goban::placeStone(uint8_t x, uint8_t y, QGo::Case color)
{
    get(x, y) = color;
    checkForCapture(x, y);
    checkForSuicide(x, y);
}

const QGo::Case& Goban::operator()(uint8_t x, uint8_t y) const throw(std::invalid_argument)
{
    if(x >= m_size || y >= m_size) throw std::invalid_argument("Index out of bound");
    return m_array[m_size*y + x];
}

Goban::type_set_point Goban::computeGroup(uint8_t x, uint8_t y) const
{
    type_set_point group;
    if((*this)(x,y) == QGo::EMPTY) return group;
    addStoneToGroup(group, Point(x, y));
    return group;
}

Goban::type_set_point Goban::computeLiberties(uint8_t x, uint8_t y) const
{
    type_set_point group = computeGroup(x, y); //computing the whole group of stone concerned

    //finding all of its liberties
    type_set_point res;
    for(const Point& point : group)
    {
        Goban::type_set_point adj = adjacentStones(point.x(), point.y());
        for(const Point& p : adj)
        {
            if((*this)(p.x(), p.y()) == QGo::EMPTY)
                res.insert(p);
        }
    }
    return res;
}

std::size_t Goban::nbStonesPlaced() const
{
    return m_array.size();
}

QGo::Case& Goban::get(uint8_t x, uint8_t y) throw(std::invalid_argument)
{
    if(x >= m_size || y >= m_size) throw std::invalid_argument("Index out of bound");
    return m_array[m_size*y + x];
}

void Goban::checkForCapture(uint8_t x, uint8_t y)
{
    QGo::Case color = (*this)(x ,y);
    type_set_point adj = adjacentStones(x, y);
    for(const Point& p : adj)
    {
        QGo::Case c = (*this)(p.x(), p.y());
        if(c != color && c!= QGo::EMPTY && computeLiberties(p.x(), p.y()).empty())
            removeGroup(p.x(), p.y());
    }
}

void Goban::checkForSuicide(uint8_t x, uint8_t y)
{
    std::set<Point> libertees = computeLiberties(x, y);
    if(computeLiberties(x, y).empty()) removeGroup(x, y); //it actually is a suicide
}

Goban::type_set_point Goban::adjacentStones(uint8_t x, uint8_t y) const
{
    type_set_point res;
    if(x > 0) res.insert(Point((uint8_t)(x-1), y));
    if(y > 0) res.insert(Point(x, (uint8_t)(y-1)));
    if(y < m_size - 1) res.insert(Point(x, (uint8_t)(y+1)));
    if(x < m_size - 1) res.insert(Point((uint8_t)(x+1), y));
    return res;
}

void Goban::addStoneToGroup(type_set_point& set, const Point& p) const
{
    std::pair<type_set_point::iterator, bool> pair = set.insert(p);
    if(!pair.second) return;
    QGo::Case color = (*this)(p.x(), p.y());
    assert(color != QGo::EMPTY);
    type_set_point directs = adjacentStones(p.x(), p.y());
    for(const Point& point : directs)
    {
        if((*this)(point.x(), point.y()) == color)
            addStoneToGroup(set, point);
    }
}

void Goban::removeGroup(uint8_t x, uint8_t y)
{
    QGo::Case colorPlayed = (*this)(x, y);
    assert(colorPlayed != QGo::EMPTY);
    type_set_point group = computeGroup(x, y); //computing the whole group of stone concerned
    for(const Point& p : group)
        get(p.x(), p.y()) = QGo::EMPTY;
}
