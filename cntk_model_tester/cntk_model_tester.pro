include(../QGo.pri)

QT -= core gui

TARGET = cntk_model_tester
TEMPLATE = app
CONFIG += console
CONFIG -= app_bundle
CONFIG -= Qt

OBJECTS_DIR = $$QGO_OBJ_CNTK_MODEL_TESTER
MOC_DIR = $$QGO_MOC_CNTK_MODEL_TESTER

INCLUDEPATH += $$QGO_SRC
INCLUDEPATH += ../lib
INCLUDEPATH += $$BOOST_INCLUDE_PATH

LIBS += -L$$QGO_BIN
LIBS += -lQGoLib
LIBS += -L$$BOOST_LIB_PATH
LIBS += -l$$BOOST_PREFIXboost_system$$BOOST_SUFFIX -l$$BOOST_PREFIXboost_filesystem$$BOOST_SUFFIX

SOURCES += main.cpp
