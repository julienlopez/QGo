#include <QTest>

#include <iostream>
using namespace std;

#include "testsgfreader.hpp"
#include "testgoban.hpp"
#include "testpoint.hpp"
#include "testboosttree.hpp"

int main(int argc, char *argv[])
{
    bool ok = true;

    TestSGFReader test1;
    ok &= (QTest::qExec(&test1, argc, argv) == 0);

    TestGoban test2;
    ok &= (QTest::qExec(&test2, argc, argv) == 0);

    TestPoint test3;
    ok &= (QTest::qExec(&test3, argc, argv) == 0);

    TestBoostTree test4;
    ok &= (QTest::qExec(&test4, argc, argv) == 0);

    if(ok) cerr << "all tests passed" << endl;
    else cerr << "some tests failed" << endl;

    return ok?EXIT_SUCCESS:EXIT_FAILURE;
}
