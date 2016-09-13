#include "catch.hpp"

#include "gobanmakinghelper.hpp"
#include "macros.hpp"

#include <goban.hpp>
#include <game.hpp>
#include <sgfreader.hpp>

TEST_CASE("TestSGFReader")
{

    SECTION("test Simple Read")
    {
        QGo::goban_sp goban(new Goban(0));
        QGo::type_list_point blackMoves = {{Point(1,1)}};
        QGo::type_list_point whiteMoves = {{Point(1,2)}};

        GobanMakingHelper::buildGoban(goban, 9, blackMoves, whiteMoves);

        REQUIRE(9 == goban->size());
        for(uint8_t x = 0; x < goban->size(); x++)
            for(uint8_t y = 0; y < goban->size(); y++)
            {
                QGo::Case c = (*goban)(x, y);
                if(std::find(blackMoves.begin(), blackMoves.end(), Point(x, y)) != blackMoves.end())
                    CHECK(QGo::BLACK == c);
                else if(std::find(whiteMoves.begin(), whiteMoves.end(), Point(x, y)) != whiteMoves.end())
                    CHECK(QGo::WHITE == c);
                else CHECK(QGo::EMPTY == c);
            }
    }

    SECTION("test Komi Parsing")
    {
        QGo::goban_sp goban(new Goban(0));
        std::list<std::string> lines = {{"SZ[9]"}, {"KM[5.5]"}};
        const Game g = SGFReader::parse(lines);
        g.loadMovesOnto(goban);
        CHECK(5.5 == g.m_komi);
    }

    SECTION("test Black Rank Parsing")
    {
        QGo::goban_sp goban(new Goban(0));
        std::list<std::string> lines = {{"SZ[9]"}, {"BR[15k]"}};
        const Game g = SGFReader::parse(lines);
        g.loadMovesOnto(goban);
        CHECK("15k" == g.blackRank());
    }

    SECTION("test White Rank Parsing")
    {
        QGo::goban_sp goban(new Goban(0));
        std::list<std::string> lines = {{"SZ[9]"}, {"WR[9k]"}};
        const Game g = SGFReader::parse(lines);
        g.loadMovesOnto(goban);
        CHECK("9k" == g.whiteRank());
    }

    SECTION("test Place Parsing")
    {
        std::string place = "Paris";
        QGo::goban_sp goban(new Goban(0));
        std::list<std::string> lines = {{"SZ[9]"}, {"PC["+place+"]"}};
        const Game g = SGFReader::parse(lines);
        g.loadMovesOnto(goban);
        CHECK(place == g.m_gamePlace);
    }

    SECTION("test Game Name Parsing")
    {
        std::string name = "Super Meijin";
        QGo::goban_sp goban(new Goban(0));
        std::list<std::string> lines = {{"SZ[9]"}, {"GN["+name+"]"}};
        const Game g = SGFReader::parse(lines);
        g.loadMovesOnto(goban);
        CHECK(name == g.m_name);
    }

    SECTION("test Number Of Handicap Stones Parsing")
    {
        uint8_t nbStones = 2;
        QGo::goban_sp goban(new Goban(0));
        std::list<std::string> lines = {{"SZ[9]"}, {"HA["+std::to_string(nbStones)+"]"}};
        const Game g = SGFReader::parse(lines);
        g.loadMovesOnto(goban);
        CHECK(nbStones == g.m_nbHandicapStones);
    }

    SECTION("test Black Name Parsing")
    {
        std::string name("Blackey");
        QGo::goban_sp goban(new Goban(0));
        std::list<std::string> lines = {{"SZ[9]"}, {"PB["+name+"]"}};
        const Game g = SGFReader::parse(lines);
        g.loadMovesOnto(goban);
        CHECK(name == g.blackName());
    }

    SECTION("test White Name Parsing")
    {
        std::string name("Whitey");
        QGo::goban_sp goban(new Goban(0));
        std::list<std::string> lines = {{"SZ[9]"}, {"PW["+name+"]"}};
        const Game g = SGFReader::parse(lines);
        g.loadMovesOnto(goban);
        CHECK(name == g.whiteName());
    }

    SECTION("test Overtime System Parsing")
    {
        std::string overtime("byo-yomi 5min 15stones");
        QGo::goban_sp goban(new Goban(0));
        std::list<std::string> lines = {{"SZ[9]"}, {"OT["+overtime+"]"}};
        const Game g = SGFReader::parse(lines);
        g.loadMovesOnto(goban);
        CHECK(overtime == g.m_overtimeSystem);
    }

    SECTION("test Copyright Parsing")
    {
        std::string copyright("free");
        QGo::goban_sp goban(new Goban(0));
        std::list<std::string> lines = {{"SZ[9]"}, {"CP["+copyright+"]"}};
        const Game g = SGFReader::parse(lines);
        g.loadMovesOnto(goban);
        CHECK(copyright == g.m_copyright);
    }

    SECTION("test Event Name Parsing")
    {
        std::string name("Super Meijin Paris");
        QGo::goban_sp goban(new Goban(0));
        std::list<std::string> lines = {{"SZ[9]"}, {"EV["+name+"]"}};
        const Game g = SGFReader::parse(lines);
        g.loadMovesOnto(goban);
        CHECK(name == g.m_eventName);
    }

    SECTION("test Date Parsing")
    {
        std::string date("Super Meijin Paris");
        QGo::goban_sp goban(new Goban(0));
        std::list<std::string> lines = {{"SZ[9]"}, {"DT["+date+"]"}};
        const Game g = SGFReader::parse(lines);
        g.loadMovesOnto(goban);
        CHECK(date == g.m_date);
    }
    SECTION("test Information Parsing")
    {
        std::string info("Some infos on the game");
        QGo::goban_sp goban(new Goban(0));
        std::list<std::string> lines = {{"SZ[9]"}, {"GC["+info+"]"}};
        const Game g = SGFReader::parse(lines);
        g.loadMovesOnto(goban);
        CHECK(info == g.m_information);
    }

    SECTION("test Rule Set Parsing")
    {
        std::string ruleset("Japanese");
        QGo::goban_sp goban(new Goban(0));
        std::list<std::string> lines = {{"SZ[9]"}, {"RU["+ruleset+"]"}};
        const Game g = SGFReader::parse(lines);
        g.loadMovesOnto(goban);
        CHECK(ruleset == g.m_ruleSet);
    }

    SECTION("test User Parsing")
    {
        std::string user("Me!");
        QGo::goban_sp goban(new Goban(0));
        std::list<std::string> lines = {{"SZ[9]"}, {"US[" + user + "]"}};
        const Game g = SGFReader::parse(lines);
        g.loadMovesOnto(goban);
        CHECK(user == g.m_user);
    }

    SECTION("test Application Parsing")
    {
        std::string app("QGo");
        QGo::goban_sp goban(new Goban(0));
        std::list<std::string> lines = {{"SZ[9]"}, {"AP["+app+"]"}};
        const Game g = SGFReader::parse(lines);
        g.loadMovesOnto(goban);
        CHECK(app == g.m_application);
    }

    SECTION("test Full Report")
    {
        QGo::goban_sp goban(new Goban(0));

        std::string name = "game";
        std::string komi = "5.5";
        std::string nbHandicapStones = "2";
        std::string blackName = "me";
        std::string blackRank = "1d";
        std::string whiteName = "you";
        std::string whiteRank = "2d";
        std::string overtimeSystem = "byo-yomi";
        std::string copyright = "copyleft";
        std::string eventName = "QGo Super Meijin";
        std::string boardSize = "19";
        std::string ruleSet = "Japanese";
        std::string gamePlace = "Paris";

        std::list<std::string> lines = {{"GN["+name+"]"}, {"KM["+komi+"]"}, {"HA["+nbHandicapStones+"]"}, {"PB["+blackName+"]"}, {"BR["+blackRank+"]"},
                                        {"PW["+whiteName+"]"}, {"WR["+whiteRank+"]"}, {"OT["+overtimeSystem+"]"}, {"CP["+copyright+"]"}, {"EV["+eventName+"]"},
                                        {"SZ["+boardSize+"]"}, {"RU["+ruleSet+"]"}, {"PC["+gamePlace+"]"}};
        Game g;
        EXPECT_NOTHROW((g = SGFReader::parse(lines)));
        g.loadMovesOnto(goban);

        std::string res = "Game Name: " + name + "\n"
         + "Komi: " + komi + "\n"
         + "Handicap stones: " + nbHandicapStones + "\n"
         + "Black: \n" + "\tname: " + blackName + "\n\trank: " + blackRank + "\n"
         + "White: \n" + "\tname: " + whiteName + "\n\trank: " + whiteRank + "\n"
         + "Overtime System: " + overtimeSystem + "\n"
         + "Copyright System: " + copyright + "\n"
         + "Event Name: " + eventName + "\n"
         + "Board Size: " + boardSize + "\n"
         + "Rule Set: " + ruleSet + "\n"
         + "Game Place: " + gamePlace + "\n";

        CHECK(res == g.report());
    }

    SECTION("test Skip Empty Line")
    {
        QGo::goban_sp goban(new Goban(0));
        std::list<std::string> lines = {{"SZ[9]"}, {""}};
        Game g;
        EXPECT_NOTHROW((g = SGFReader::parse(lines)));
        g.loadMovesOnto(goban);
        CHECK(g.m_boardSize == 9);
    }

    SECTION("test Throw On Invalid Line 1")
    {
        QGo::goban_sp goban(new Goban(0));
        std::list<std::string> lines = {{"SZ[9]"}, {"B5]"}};
        Game g;
        EXPECT_THROW((g = SGFReader::parse(lines)), SGFReader::InvalidLine);
    }

    SECTION("test Throw On Invalid Line 2")
    {
        QGo::goban_sp goban(new Goban(0));
        std::list<std::string> lines = {{"SZ[9]"}, {"B[5"}};
        Game g;
        EXPECT_THROW((g = SGFReader::parse(lines)), SGFReader::InvalidLine);
    }

    SECTION("test Throw On Invalid Reckognized Line")
    {
        QGo::goban_sp goban(new Goban(0));
        std::list<std::string> lines = {{"SZ[9]"}, {"PP[11]"}};
        Game g;
        EXPECT_THROW((g = SGFReader::parse(lines)), SGFReader::UnreckognizedCommand);
    }

    SECTION("test Throw On Unsupported Sgf Format")
    {
        QGo::goban_sp goban(new Goban(0));
        std::list<std::string> lines = {{"SZ[9]"}, {"FF[3]"}};
        Game g;
        EXPECT_THROW((g = SGFReader::parse(lines)), SGFReader::InvalidLine);
    }

    SECTION("test No Throw On Supported Sgf Format")
    {
        QGo::goban_sp goban(new Goban(0));
        std::list<std::string> lines = {{"SZ[9]"}, {"FF[4]"}};
        Game g;
        EXPECT_NOTHROW(g = SGFReader::parse(lines));
    }

    SECTION("test Throw On Not A Game Of Go")
    {
        QGo::goban_sp goban(new Goban(0));
        std::list<std::string> lines = {{"SZ[9]"}, {"GM[3]"}};
        Game g;
        EXPECT_THROW((g = SGFReader::parse(lines)), SGFReader::InvalidLine);
    }

    SECTION("test No Throw On Game Of Go")
    {
        QGo::goban_sp goban(new Goban(0));
        std::list<std::string> lines = {{"SZ[9]"}, {"GM[1]"}};
        Game g;
        EXPECT_NOTHROW(g = SGFReader::parse(lines));
    }

    SECTION("test Parse High Position")
    {
        std::list<std::string> lines = {{"SZ[32]"}, {";B[Bc]"}};
        Game g;
        EXPECT_NOTHROW((g = SGFReader::parse(lines)));
    }

    SECTION("test Invalid Position")
    {
        std::list<std::string> lines = {{"SZ[32]"}, {";B[12]"}};
        Game g;
        EXPECT_THROW((g = SGFReader::parse(lines)), SGFReader::InvalidLine);
    }

    SECTION("test Parse Alternative Move 1")
    {
        QGo::goban_sp goban(new Goban(0));
        std::list<std::string> lines = {{"SZ[9]"}, {";B[aa]"}, {"("}, {";W[bb]"}, {")"}, {"("}, {";W[bc]"}, {")"}};
        Game g;
        EXPECT_NOTHROW((g = SGFReader::parse(lines)));
        const Game::type_tree& tree = g.tree();
        REQUIRE(tree.nbRoots() == 1);
        Game::type_tree::vertex_descriptor root = tree.roots().front();

        Game::Move move = tree(root);
        CHECK(QGo::BLACK == move.color());
        CHECK(Point(0,0) == move.position());

        REQUIRE(tree.nbChildren(root) == 2);
        for(std::size_t i = 0; i < 2; i++)
        {
            Game::type_tree::vertex_descriptor c = tree.child(root, i);
            CHECK(tree.nbChildren(c) == 0);
            move = tree(c);
            CHECK(QGo::WHITE == move.color());
            CHECK((i==0?Point(1, 1):Point(1, 2)) == move.position());
        }
    }

}
