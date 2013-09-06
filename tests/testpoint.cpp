#include "testpoint.hpp"

#include <point.hpp>

#include <QTest>

TestPoint::TestPoint(QObject *parent) :
    QObject(parent)
{}

void TestPoint::testSetters()
{
    Point p(0, 0);
    p.setX(1);
    p.setY(2);
    QCOMPARE((uint8_t)1, p.x());
    QCOMPARE((uint8_t)2, p.y());
}

void TestPoint::testComparisonOperators()
{
    Point p1(0, 0);
    Point p2(0, 0);
    Point p3(1, 2);
    QVERIFY(p1 == p2);
    QVERIFY(p1 != p3);
}
