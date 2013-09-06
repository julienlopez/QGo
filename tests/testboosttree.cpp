#include "testboosttree.hpp"

#include <utils/boosttree.hpp>

#include <QTest>

TestBoostTree::TestBoostTree(QObject *parent) :
    QObject(parent)
{}

void TestBoostTree::testAddOneRoot()
{
    utils::BoostTree<int> tree;
    QCOMPARE(tree.nbRoots(), (std::size_t)0);
    tree.addNode(2);
    QCOMPARE(tree.nbRoots(), (std::size_t)1);
    utils::BoostTree<int>::vertex_descriptor root = tree.roots().front();
    QVERIFY(tree.children(root).empty());
    QCOMPARE(tree(root), 2);
}

void TestBoostTree::testAddTwoRoots()
{
    utils::BoostTree<int> tree;
    QCOMPARE(tree.nbRoots(), (std::size_t)0);
    tree.addNode(2);
    QCOMPARE(tree.nbRoots(), (std::size_t)1);
    tree.addNode(5);
    QCOMPARE(tree.nbRoots(), (std::size_t)2);
    utils::BoostTree<int>::vertex_descriptor root = tree.roots().front();
    QVERIFY(tree.children(root).empty());
    QCOMPARE(tree(root), 2);
    root = tree.roots().back();
    QVERIFY(tree.children(root).empty());
    QCOMPARE(tree(root), 5);
}
