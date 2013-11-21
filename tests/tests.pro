include(../QGo.pri)

QT += core testlib
QT -= gui

TARGET = tests
TEMPLATE = app
CONFIG += console
CONFIG -= app_bundle

OBJECTS_DIR = $$QGO_OBJ_TESTS
MOC_DIR = $$QGO_MOC_TESTS

INCLUDEPATH += $$QGO_SRC

QMAKE_CXX += -g --coverage
QMAKE_LFLAGS += --coverage

QMAKE_CXXFLAGS -= -O2
QMAKE_CXXFLAGS += -O0
QMAKE_CXXFLAGS_DEBUG -= -O2
QMAKE_CXXFLAGS_DEBUG += -O0
QMAKE_CXXFLAGS_RELEASE -= -O2
QMAKE_CXXFLAGS_RELEASE += -O0

SOURCES += main.cpp \
    ../src/point.cpp \
    ../src/game.cpp \
    ../src/goban.cpp \
    ../src/sgfreader.cpp \
    ../src/scorecomputer.cpp \
    testsgfreader.cpp \
    testgoban.cpp \
    gobanmakinghelper.cpp \
    testpoint.cpp \
    testboosttree.cpp

HEADERS += \
    ../src/globals.hpp \
    ../src/point.hpp \
    ../src/game.hpp \
    ../src/goban.hpp \
    ../src/sgfreader.hpp \
    ../src/utils/boosttree.hpp \
    ../src/scorecomputer.hpp \
    testsgfreader.hpp \
    testgoban.hpp \
    gobanmakinghelper.hpp \
    testpoint.hpp \
    macros.hpp \
    testboosttree.hpp

