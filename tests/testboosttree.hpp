#ifndef TESTLINKEDTREE_HPP
#define TESTLINKEDTREE_HPP

#include <QObject>

class TestBoostTree : public QObject
{
    Q_OBJECT
public:
    explicit TestBoostTree(QObject *parent = 0);

private slots:
    void testAddOneRoot();
    void testAddTwoRoots();
};

#endif // TESTLINKEDTREE_HPP
