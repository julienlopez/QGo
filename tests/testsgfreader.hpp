#ifndef TESTSGFREADER_HPP
#define TESTSGFREADER_HPP

#include <QObject>

class TestSGFReader : public QObject
{
    Q_OBJECT
public:
    explicit TestSGFReader(QObject *parent = 0);
    
private slots:
    void testSimpleRead();

    void testKomiParsing();
    void testBlackRankParsing();
    void testWhiteRankParsing();
    void testPlaceParsing();
    void testGameNameParsing();
    void testNumberOfHandicapStonesParsing();
    void testBlackNameParsing();
    void testWhiteNameParsing();
    void testOvertimeSystemParsing();
    void testCopyrightParsing();
    void testEventNameParsing();
    void testDateParsing();
    void testInformationParsing();
    void testRuleSetParsing();
    void testApplicationParsing();

    void testFullReport();

    void testSkipEmptyLine();
    void testThrowOnInvalidLine1();
    void testThrowOnInvalidLine2();
    void testThrowOnInvalidReckognizedLine();
    void testThrowOnUnsupportedSgfFormat();
    void testNoThrowOnSupportedSgfFormat();
    void testThrowOnNotAGameOfGo();
    void testNoThrowOnGameOfGo();

    void testParseHighPosition();
    void testInvalidPosition();

    void testParseAlternativeMove1();
};

#endif // TESTSGFREADER_HPP
