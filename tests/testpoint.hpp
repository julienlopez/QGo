#ifndef TESTPOINT_HPP
#define TESTPOINT_HPP

#include <QObject>

class TestPoint : public QObject
{
    Q_OBJECT
public:
    explicit TestPoint(QObject *parent = 0);
    
private slots:
    void testSetters();
    void testComparisonOperators();
    
};

#endif // TESTPOINT_HPP
