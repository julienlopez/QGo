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
            QGo::Case c = (*goban)(x, y);
            if(std::find(blackMoves.begin(), blackMoves.end(), Point(x, y)) != blackMoves.end())
                QCOMPARE(QGo::BLACK, c);
            else if(std::find(whiteMoves.begin(), whiteMoves.end(), Point(x, y)) != whiteMoves.end())
                QCOMPARE(QGo::WHITE, c);
            else QCOMPARE(QGo::EMPTY, c);
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

void TestSGFReader::testApplicationParsing()
{
    std::string app("QGo");
    QGo::goban_sp goban(new Goban(0));
    std::list<std::string> lines = {{"SZ[9]"}, {"AP["+app+"]"}};
    Game g = SGFReader::parse(lines);
    g.loadMovesOnto(goban);
    QCOMPARE(app, g.application());
}

void TestSGFReader::testFullReport()
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

    QCOMPARE(res, g.report());
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

void TestSGFReader::testThrowOnInvalidLine1()
{
    QGo::goban_sp goban(new Goban(0));
    std::list<std::string> lines = {{"SZ[9]"}, {"B5]"}};
    Game g;
    EXPECT_THROW((g = SGFReader::parse(lines)), SGFReader::InvalidLine);
}

void TestSGFReader::testThrowOnInvalidLine2()
{
    QGo::goban_sp goban(new Goban(0));
    std::list<std::string> lines = {{"SZ[9]"}, {"B[5"}};
    Game g;
    EXPECT_THROW((g = SGFReader::parse(lines)), SGFReader::InvalidLine);
}

void TestSGFReader::testThrowOnInvalidReckognizedLine()
{
    QGo::goban_sp goban(new Goban(0));
    std::list<std::string> lines = {{"SZ[9]"}, {"PP[11]"}};
    Game g;
    EXPECT_THROW((g = SGFReader::parse(lines)), SGFReader::UnreckognizedCommand);
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

void TestSGFReader::testParseAlternativeMove1()
{
    QGo::goban_sp goban(new Goban(0));
    std::list<std::string> lines = {{"SZ[9]"}, {";B[aa]"}, {"("}, {";W[bb]"}, {")"}, {"("}, {";W[bc]"}, {")"}};
    Game g;
    EXPECT_NOTHROW((g = SGFReader::parse(lines)));
    const Game::type_tree& tree = g.tree();
    QCOMPARE((std::size_t)1, tree.nbRoots());
    Game::type_tree::vertex_descriptor root = tree.roots().front();

    Game::Move move = tree(root);
    QCOMPARE(QGo::BLACK, move.color());
    QCOMPARE(Point(0,0), move.position());

    QCOMPARE((std::size_t)2, tree.nbChildren(root));
    for(std::size_t i = 0; i < 2; i++)
    {
        Game::type_tree::vertex_descriptor c = tree.child(root, i);
        QCOMPARE((std::size_t)0, tree.nbChildren(c));
        move = tree(c);
        QCOMPARE(QGo::WHITE, move.color());
        QCOMPARE((i==0?Point(1, 1):Point(1, 2)), move.position());
    }
}
