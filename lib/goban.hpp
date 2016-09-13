#ifndef GOBAN_HPP
#define GOBAN_HPP

#include <point.hpp>

#include <set>
#include <vector>
#include <stdexcept>

class Goban
{
public:

    typedef QGo::type_set_point type_set_point;

    Goban(uint8_t size);

    void resize(uint8_t newSize);

    uint8_t size() const;

    void placeStone(uint8_t x, uint8_t y, QGo::Case color);

    const QGo::Case& operator()(uint8_t x, uint8_t y) const throw(std::invalid_argument);

    type_set_point computeGroup(uint8_t x, uint8_t y) const;

    /**
    * \brief returns all the liberties (adjacent positions) to the group at (x,y)
    */
    type_set_point computeLiberties(uint8_t x, uint8_t y) const;

    /**
     * @brief compute the number of stones currently on the goban.
     * @return the number of stones placed on the goban
     */
    std::size_t nbStonesPlaced() const;

    /**
     * @brief clear reset the board clean, removing all the stones.
     */
    void clear();

protected:
    QGo::Case& get(uint8_t x, uint8_t y) throw(std::invalid_argument);

private:
    uint8_t m_size;
    std::vector<QGo::Case> m_array;

    /**
    * \brief check if the move at (x,y) captures anything
    */
    void checkForCapture(uint8_t x, uint8_t y);

    /**
    * \brief check if the move at (x,y) is a suicide
    */
    void checkForSuicide(uint8_t x, uint8_t y);

    /**
    * \brief returns the positions of all the adjacent stones to the stone at (x,y), so four points top.
    */
    type_set_point adjacentStones(uint8_t x, uint8_t y) const;

    /**
    * \brief recursively add a stone to a group, then all it's direct neighbours.
    */
    void addStoneToGroup(type_set_point& set, const Point& p) const;

    /**
    * \brief removes from the game the whole group located at (x,y)
    *
    * Basically, removes the stone at (x,y) and all the other ones (of the same color) connected to it
    */
    void removeGroup(uint8_t x, uint8_t y);
};

#endif // GOBAN_HPP
