include(../QGo.pri)

QT += core
QT -= gui

TARGET = cntk_converter
TEMPLATE = app
CONFIG += console
CONFIG -= app_bundle

OBJECTS_DIR = $$QGO_OBJ_CNTK_CONVERTER
MOC_DIR = $$QGO_MOC_CNTK_CONVERTER

INCLUDEPATH += $$QGO_SRC
INCLUDEPATH += ../lib
INCLUDEPATH += $$BOOST_INCLUDE_PATH

LIBS += -L$$QGO_BIN
LIBS += -lQGoLib
LIBS += -L$$BOOST_LIB_PATH
LIBS += -l$$BOOST_PREFIXboost_system$$BOOST_SUFFIX -l$$BOOST_PREFIXboost_filesystem$$BOOST_SUFFIX

SOURCES += main.cpp
