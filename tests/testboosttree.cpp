#include "catch.hpp"

#include <utils/boosttree.hpp>

TEST_CASE("Test Boost Tree")
{

    SECTION("test Add One Root")
    {
        utils::BoostTree<int> tree;
        CHECK(tree.nbRoots() == 0);
        tree.addNode(2);
        CHECK(tree.nbRoots() == 1);
        utils::BoostTree<int>::vertex_descriptor root = tree.roots().front();
        CHECK(tree.children(root).empty());
        CHECK(tree(root) == 2);
    }

    SECTION("test Add Two Roots")
    {
        utils::BoostTree<int> tree;
        CHECK(tree.nbRoots() == 0);
        tree.addNode(2);
        CHECK(tree.nbRoots() == 1);
        tree.addNode(5);
        CHECK(tree.nbRoots() == 2);
        utils::BoostTree<int>::vertex_descriptor root = tree.roots().front();
        CHECK(tree.children(root).empty());
        CHECK(tree(root) == 2);
        root = tree.roots().back();
        CHECK(tree.children(root).empty());
        CHECK(tree(root) == 5);
    }

}
