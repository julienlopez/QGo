#include "catch.hpp"

#include "point.hpp"

TEST_CASE("TestPoint")
{

    SECTION("test Setters")
    {
        Point p(0, 0);
        p.setX(1);
        p.setY(2);
        CHECK(1 == p.x());
        CHECK(2 == p.y());
    }

    SECTION("test Comparison Operators")
    {
        Point p1(0, 0);
        Point p2(0, 0);
        Point p3(1, 2);
        CHECK(p1 == p2);
        CHECK(p1 != p3);
    }

}
