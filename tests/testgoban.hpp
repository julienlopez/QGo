#ifndef TESTGOBAN_HPP
#define TESTGOBAN_HPP

#include <QObject>

class TestGoban : public QObject
{
    Q_OBJECT
public:
    explicit TestGoban(QObject *parent = 0);
    
private slots:
    void testcomputeGroup1();
    void testcomputeGroup2();

    void testPlaceStoneSuicide();
    void testPlaceStoneCapture();
};

#endif // TESTGOBAN_HPP
