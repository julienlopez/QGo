#include "testsgfreader.hpp"
#include "gobanmakinghelper.hpp"
#include "macros.hpp"

#include <goban.hpp>
#include <game.hpp>
#include <sgfreader.hpp>

TestSGFReader::TestSGFReader(QObject *parent) :
    QObject(parent)
{}

void TestSGFReader::testSimpleRead()
{
    QGo::goban_sp goban(new Goban(0));
    QGo::type_list_point blackMoves = {{Point(1,1)}};
    QGo::type_list_point whiteMoves = {{Point(1,2)}};

    GobanMakingHelper::buildGoban(goban, 9, blackMoves, whiteMoves);

    QCOMPARE((uint8_t)9, goban->size());
    for(uint8_t x = 0; x < goban->size(); x++)
        for(uint8_t y = 0; y < goban->size(); y++)
        {
            Goban::Case c = (*goban)(x, y);
            if(std::find(blackMoves.begin(), blackMoves.end(), Point(x, y)) != blackMoves.end())
                QCOMPARE(Goban::BLACK, c);
            else if(std::find(whiteMoves.begin(), whiteMoves.end(), Point(x, y)) != whiteMoves.end())
                QCOMPARE(Goban::WHITE, c);
            else QCOMPARE(Goban::EMPTY, c);
        }
}

void TestSGFReader::testKomiParsing()
{
    QGo::goban_sp goban(new Goban(0));
    std::list<std::string> lines = {{"SZ[9]"}, {"KM[5.5]"}};
    Game g = SGFReader::parse(lines);
    g.loadMovesOnto(goban);
    QCOMPARE(5.5, g.komi());
}

void TestSGFReader::testBlackRankParsing()
{
    QGo::goban_sp goban(new Goban(0));
    std::list<std::string> lines = {{"SZ[9]"}, {"BR[15k]"}};
    Game g = SGFReader::parse(lines);
    g.loadMovesOnto(goban);
    QCOMPARE(std::string("15k"), g.blackRank());
}

void TestSGFReader::testWhiteRankParsing()
{
    QGo::goban_sp goban(new Goban(0));
    std::list<std::string> lines = {{"SZ[9]"}, {"WR[9k]"}};
    Game g = SGFReader::parse(lines);
    g.loadMovesOnto(goban);
    QCOMPARE(std::string("9k"), g.whiteRank());
}

void TestSGFReader::testPlaceParsing()
{
    std::string place = "Paris";
    QGo::goban_sp goban(new Goban(0));
    std::list<std::string> lines = {{"SZ[9]"}, {"PC["+place+"]"}};
    Game g = SGFReader::parse(lines);
    g.loadMovesOnto(goban);
    QCOMPARE(place, g.gamePlace());
}

void TestSGFReader::testGameNameParsing()
{
    std::string name = "Super Meijin";
    QGo::goban_sp goban(new Goban(0));
    std::list<std::string> lines = {{"SZ[9]"}, {"GN["+name+"]"}};
    Game g = SGFReader::parse(lines);
    g.loadMovesOnto(goban);
    QCOMPARE(name, g.name());
}

void TestSGFReader::testNumberOfHandicapStonesParsing()
{
    uint8_t nbStones = 2;
    QGo::goban_sp goban(new Goban(0));
    std::list<std::string> lines = {{"SZ[9]"}, {"HA["+std::to_string(nbStones)+"]"}};
    Game g = SGFReader::parse(lines);
    g.loadMovesOnto(goban);
    QCOMPARE(nbStones, g.nbHandicapStones());
}

void TestSGFReader::testBlackNameParsing()
{
    std::string name("Blackey");
    QGo::goban_sp goban(new Goban(0));
    std::list<std::string> lines = {{"SZ[9]"}, {"PB["+name+"]"}};
    Game g = SGFReader::parse(lines);
    g.loadMovesOnto(goban);
    QCOMPARE(name, g.blackName());
}

void TestSGFReader::testWhiteNameParsing()
{
    std::string name("Whitey");
    QGo::goban_sp goban(new Goban(0));
    std::list<std::string> lines = {{"SZ[9]"}, {"PW["+name+"]"}};
    Game g = SGFReader::parse(lines);
    g.loadMovesOnto(goban);
    QCOMPARE(name, g.whiteName());
}

void TestSGFReader::testOvertimeSystemParsing()
{
    std::string overtime("byo-yomi 5min 15stones");
    QGo::goban_sp goban(new Goban(0));
    std::list<std::string> lines = {{"SZ[9]"}, {"OT["+overtime+"]"}};
    Game g = SGFReader::parse(lines);
    g.loadMovesOnto(goban);
    QCOMPARE(overtime, g.overtimeSystem());
}

void TestSGFReader::testCopyrightParsing()
{
    std::string copyright("free");
    QGo::goban_sp goban(new Goban(0));
    std::list<std::string> lines = {{"SZ[9]"}, {"CP["+copyright+"]"}};
    Game g = SGFReader::parse(lines);
    g.loadMovesOnto(goban);
    QCOMPARE(copyright, g.copyright());
}

void TestSGFReader::testEventNameParsing()
{
    std::string name("Super Meijin Paris");
    QGo::goban_sp goban(new Goban(0));
    std::list<std::string> lines = {{"SZ[9]"}, {"EV["+name+"]"}};
    Game g = SGFReader::parse(lines);
    g.loadMovesOnto(goban);
    QCOMPARE(name, g.eventName());
}

void TestSGFReader::testDateParsing()
{
    std::string date("Super Meijin Paris");
    QGo::goban_sp goban(new Goban(0));
    std::list<std::string> lines = {{"SZ[9]"}, {"DT["+date+"]"}};
    Game g = SGFReader::parse(lines);
    g.loadMovesOnto(goban);
    QCOMPARE(date, g.date());
}
void TestSGFReader::testInformationParsing()
{
    std::string info("Some infos on the game");
    QGo::goban_sp goban(new Goban(0));
    std::list<std::string> lines = {{"SZ[9]"}, {"GC["+info+"]"}};
    Game g = SGFReader::parse(lines);
    g.loadMovesOnto(goban);
    QCOMPARE(info, g.information());
}

void TestSGFReader::testRuleSetParsing()
{
    std::string ruleset("Japanese");
    QGo::goban_sp goban(new Goban(0));
    std::list<std::string> lines = {{"SZ[9]"}, {"RU["+ruleset+"]"}};
    Game g = SGFReader::parse(lines);
    g.loadMovesOnto(goban);
    QCOMPARE(ruleset, g.ruleSet());
}

void TestSGFReader::testSkipEmptyLine()
{
    QGo::goban_sp goban(new Goban(0));
    std::list<std::string> lines = {{"SZ[9]"}, {""}};
    Game g;
    EXPECT_NOTHROW((g = SGFReader::parse(lines)));
    g.loadMovesOnto(goban);
    QCOMPARE((uint8_t)9, g.boardSize());
}

void TestSGFReader::testThrowOnInvalidLine()
{
    QGo::goban_sp goban(new Goban(0));
    std::list<std::string> lines = {{"SZ[9]"}, {"a"}};
    Game g;
    EXPECT_THROW((g = SGFReader::parse(lines)), SGFReader::UnreckognizedCommand);
}

void TestSGFReader::testThrowOnInvalidReckognizedLine()
{
    QGo::goban_sp goban(new Goban(0));
    std::list<std::string> lines = {{"SZ[9]"}, {"KM"}};
    Game g;
    EXPECT_THROW((g = SGFReader::parse(lines)), SGFReader::InvalidLine);
}

void TestSGFReader::testThrowOnUnsupportedSgfFormat()
{
    QGo::goban_sp goban(new Goban(0));
    std::list<std::string> lines = {{"SZ[9]"}, {"FF[3]"}};
    Game g;
    EXPECT_THROW((g = SGFReader::parse(lines)), SGFReader::InvalidLine);
}

void TestSGFReader::testNoThrowOnSupportedSgfFormat()
{
    QGo::goban_sp goban(new Goban(0));
    std::list<std::string> lines = {{"SZ[9]"}, {"FF[4]"}};
    Game g;
    EXPECT_NOTHROW(g = SGFReader::parse(lines));
}

void TestSGFReader::testThrowOnNotAGameOfGo()
{
    QGo::goban_sp goban(new Goban(0));
    std::list<std::string> lines = {{"SZ[9]"}, {"GM[3]"}};
    Game g;
    EXPECT_THROW((g = SGFReader::parse(lines)), SGFReader::InvalidLine);
}

void TestSGFReader::testNoThrowOnGameOfGo()
{
    QGo::goban_sp goban(new Goban(0));
    std::list<std::string> lines = {{"SZ[9]"}, {"GM[1]"}};
    Game g;
    EXPECT_NOTHROW(g = SGFReader::parse(lines));
}

void TestSGFReader::testParseHighPosition()
{
    std::list<std::string> lines = {{"SZ[32]"}, {";B[Bc]"}};
    Game g;
    EXPECT_NOTHROW((g = SGFReader::parse(lines)));
}

void TestSGFReader::testInvalidPosition()
{
    std::list<std::string> lines = {{"SZ[32]"}, {";B[12]"}};
    Game g;
    EXPECT_THROW((g = SGFReader::parse(lines)), SGFReader::InvalidLine);
}
