include(../QGo.pri)

QT += core testlib
QT -= gui

TARGET = tests
TEMPLATE = app
CONFIG += console
CONFIG -= app_bundle

OBJECTS_DIR = $$QGO_OBJ_TESTS
MOC_DIR = $$QGO_MOC_TESTS

INCLUDEPATH += $$QGO_SRC $$QGO_3RD_PARTY_INCLUDE
INCLUDEPATH += ../lib
INCLUDEPATH += $$BOOST_INCLUDE_PATH

LIBS += -L$$QGO_BIN
LIBS += -lQGoLib
LIBS += -L$$BOOST_LIB_PATH
LIBS += -l$$BOOST_PREFIXboost_system$$BOOST_SUFFIX -l$$BOOST_PREFIXboost_filesystem$$BOOST_SUFFIX

QMAKE_CXX += -g --coverage
QMAKE_LFLAGS += --coverage

QMAKE_CXXFLAGS -= -O2
QMAKE_CXXFLAGS += -O0
QMAKE_CXXFLAGS_DEBUG -= -O2
QMAKE_CXXFLAGS_DEBUG += -O0
QMAKE_CXXFLAGS_RELEASE -= -O2
QMAKE_CXXFLAGS_RELEASE += -O0

SOURCES += main.cpp \
    testsgfreader.cpp \
    testgoban.cpp \
    gobanmakinghelper.cpp \
    testpoint.cpp \
    testboosttree.cpp

HEADERS += \
    gobanmakinghelper.hpp \
    macros.hpp

