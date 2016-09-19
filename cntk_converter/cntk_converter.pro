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

LIBS += -L$$QGO_BIN
LIBS += -lQGoLib
LIBS += -lboost_system$$BOOST_SUFFIX -lboost_filesystem$$BOOST_SUFFIX

SOURCES += main.cpp \
    cntkwriter.cpp

HEADERS += \
    cntkwriter.hpp
