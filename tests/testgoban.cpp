#include "catch.hpp"

#include "gobanmakinghelper.hpp"

#include <goban.hpp>

namespace
{
    template<class T, class U>
    void compareGroups(const T& expected, const U& actual)
    {
        CHECK(expected.size() == actual.size());
        for(const typename T::value_type& t : expected)
        {
            if(std::find(actual.begin(), actual.end(), t) == actual.end())
            {
                FAIL("unable to find a value");
            }
        }
    }
}

TEST_CASE("TestGoban")
{

    SECTION("test compute Group 1")
    {
        QGo::goban_sp goban(new Goban(0));
        QGo::type_list_point blackMoves = {{Point(1,1), Point(2,1), Point(3,1)}};
        QGo::type_list_point whiteMoves = {{Point(1,2), Point(2,2), Point(3,2)}};

        GobanMakingHelper::buildGoban(goban, 9, blackMoves, whiteMoves);

        Goban::type_set_point blackGroup = goban->computeGroup(1, 1);
        compareGroups(blackMoves, blackGroup);

        Goban::type_set_point whiteGroup = goban->computeGroup(1, 2);
        compareGroups(whiteMoves, whiteGroup);
    }

    SECTION("test compute Group 2")
    {
        QGo::goban_sp goban(new Goban(0));
        QGo::type_list_point blackMoves = {{Point(1,1), Point(2,1), Point(3,1), Point(4,2)}};
        QGo::type_list_point whiteMoves = {{Point(1,2), Point(2,2), Point(3,2), Point(0, 1)}};

        GobanMakingHelper::buildGoban(goban, 9, blackMoves, whiteMoves);

        Goban::type_set_point blackGroup = goban->computeGroup(1, 1);
        QGo::type_list_point expectedBlackGroup = {{Point(1,1), Point(2,1), Point(3,1)}};
        compareGroups(expectedBlackGroup, blackGroup);

        Goban::type_set_point whiteGroup = goban->computeGroup(2, 2);
        QGo::type_list_point expectedWhiteGroup = {{Point(1,2), Point(2,2), Point(3,2)}};
        compareGroups(expectedWhiteGroup, whiteGroup);
    }

    SECTION("test Place Stone Suicide")
    {
        QGo::goban_sp goban(new Goban(0));
        QGo::type_list_point blackMoves = {{Point(1,0), Point(0,1), Point(2,1), Point(1,2)}};
    //    QGo::type_list_point whiteMoves = {{Point(1,2), Point(2,2), Point(3,2), Point(0, 1)}};
        GobanMakingHelper::buildGoban(goban, 9, blackMoves, {{}});
        std::size_t nbStones = goban->nbStonesPlaced();
        goban->placeStone(1, 1, QGo::Case::WHITE);
        CHECK(nbStones == goban->nbStonesPlaced());
    }

    SECTION("test Place Stone Capture")
    {
        QGo::goban_sp goban(new Goban(0));
        QGo::type_list_point blackMoves = {{Point(1,0), Point(0,1), Point(1,2)}};
        QGo::type_list_point whiteMoves = {{Point(1,1)}};
        GobanMakingHelper::buildGoban(goban, 9, blackMoves, whiteMoves);
        std::size_t nbStones = goban->nbStonesPlaced();
        goban->placeStone(2, 1, QGo::Case::BLACK);
        CHECK(nbStones == goban->nbStonesPlaced());
        CHECK(QGo::Case::EMPTY == (*goban)(1, 1));
        CHECK(QGo::Case::BLACK == (*goban)(2, 1));
    }

}
