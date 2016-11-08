include(../QGo.pri)

QT += core gui widgets

TARGET = QGoLib
TEMPLATE = lib

CONFIG += staticlib

INCLUDEPATH += .
INCLUDEPATH += $$BOOST_INCLUDE_PATH

OBJECTS_DIR = $$QGO_OBJ_LIB
MOC_DIR = $$QGO_MOC_LIB

QMAKE_CXX += -g --coverage
QMAKE_LFLAGS += --coverage

LIBS += -L$$BOOST_LIB_PATH
LIBS += -l$$BOOST_PREFIXboost_system$$BOOST_SUFFIX -l$$BOOST_PREFIXboost_filesystem$$BOOST_SUFFIX

SOURCES += engine.cpp \
    goban.cpp \
    sgfreader.cpp \
    game.cpp \
    point.cpp \
    utils/utils.cpp \
    scorecomputer.cpp \
    neuralnetworks/neuralnetwork.cpp

HEADERS  += goban.hpp \
    globals.hpp \
    engine.hpp \
    sgfreader.hpp \
    game.hpp \
    point.hpp \
    utils/singleton.hpp \
    utils/noninstanciable.hpp \
    utils/noncopiable.hpp \
    utils/utils.hpp \
    utils/factorywithautoid.hpp \
    utils/defaultfactorystoragepolicies.hpp \
    utils/defaultfactoryerrorpolicy.hpp \
    utils/factory.hpp \
    utils/parametertrait.hpp \
    utils/tree.hpp \
    utils/boosttree.hpp \
    scorecomputer.hpp \
    neuralnetworks/neuralnetwork.hpp
