include(../QGo.pri)

QT += core gui widgets

TARGET = QGo
TEMPLATE = app

INCLUDEPATH += .
INCLUDEPATH += ../lib

LIBS += -L$$QGO_BIN
LIBS += -lQGoLib
LIBS += -lboost_system$$BOOST_SUFFIX -lboost_filesystem$$BOOST_SUFFIX

OBJECTS_DIR = $$QGO_OBJ
MOC_DIR = $$QGO_MOC

SOURCES += main.cpp\
    ui/mainwindow.cpp \
    ui/gobanwidget.cpp \
    states/state.cpp \
    states/statemanager.cpp \
    states/placestone.cpp \
    states/markgroup.cpp \
    states/countliberties.cpp \
    ui/statetoolbaraction.cpp \
    ui/imainwindow.cpp \
    states/markliberties.cpp \
    treemodel.cpp \
    ui/gametreewidget.cpp \
    ui/statetooltipsingleton.cpp \
    ui/statelesstooltipsingleton.cpp \
    ui/scorecomputeraction.cpp

HEADERS  += ui/mainwindow.hpp \
    ui/gobanwidget.hpp \
    states/state.hpp \
    states/statemanager.hpp \
    states/placestone.hpp \
    states/statefactory.hpp \
    states/crtp_state.hpp \
    states/markgroup.hpp \
    states/countliberties.hpp \
    ui/statetoolbaraction.hpp \
    ui/imainwindow.hpp \
    states/markliberties.hpp \
    treemodel.hpp \
    ui/gametreewidget.hpp \
    ui/statetooltipsingleton.hpp \
    ui/statelesstooltipsingleton.hpp
