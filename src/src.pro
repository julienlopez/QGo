include(../QGo.pri)

QT += core gui
greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = QGo
TEMPLATE = app

INCLUDEPATH += .

OBJECTS_DIR = $$QGO_OBJ
MOC_DIR = $$QGO_MOC

SOURCES += main.cpp\
    ui/mainwindow.cpp \
    ui/gobanwidget.cpp \
    engine.cpp \
    goban.cpp \
    sgfreader.cpp \
    game.cpp \
    point.cpp \
    states/state.cpp \
    states/statemanager.cpp \
    utils/utils.cpp \
    states/placestone.cpp \
    ui/tooltipsingleton.cpp \
    states/markgroup.cpp \
    states/countliberties.cpp \
    ui/statetoolbaraction.cpp \
    ui/imainwindow.cpp \
    states/markliberties.cpp \
    treemodel.cpp \
    ui/gametreewidget.cpp

HEADERS  += ui/mainwindow.hpp \
    ui/gobanwidget.hpp \
    goban.hpp \
    globals.hpp \
    engine.hpp \
    sgfreader.hpp \
    game.hpp \
    point.hpp \
    states/state.hpp \
    states/statemanager.hpp \
    utils/singleton.hpp \
    utils/noninstanciable.hpp \
    utils/noncopiable.hpp \
    utils/utils.hpp \
    states/placestone.hpp \
    utils/factorywithautoid.hpp \
    utils/defaultfactorystoragepolicies.hpp \
    utils/defaultfactoryerrorpolicy.hpp \
    states/statefactory.hpp \
    utils/factory.hpp \
    utils/parametertrait.hpp \
    states/crtp_state.hpp \
    ui/tooltipsingleton.hpp \
    states/markgroup.hpp \
    states/countliberties.hpp \
    ui/statetoolbaraction.hpp \
    ui/imainwindow.hpp \
    states/markliberties.hpp \
    utils/tree.hpp \
    utils/boosttree.hpp \
    treemodel.hpp \
    ui/gametreewidget.hpp
