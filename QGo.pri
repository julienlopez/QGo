QGO_ROOT = $$PWD

QGO_INCLUDE = $$QGO_ROOT/include/ 

QGO_3RD_PARTY_INCLUDE = $$QGO_ROOT/3rd_party/

QGO_BIN = $$QGO_ROOT/bin

QGO_OBJ_LIB = $$QGO_ROOT/obj_lib

QGO_MOC_LIB = $$QGO_ROOT/moc_lib

QGO_OBJ = $$QGO_ROOT/obj

QGO_MOC = $$QGO_ROOT/moc

QGO_OBJ_TESTS = $$QGO_ROOT/obj_tests

QGO_MOC_TESTS = $$QGO_ROOT/moc_tests

QGO_SRC = $$QGO_ROOT/src

#QGO_INSTALL_PLUGINS = $$QGO_BIN/plugins

#INCLUDEPATH += $$QGO_ROOT/common/

#INCLUDEPATH += $$QGO_INCLUDE

#DEPENDPATH += $$QGO_INCLUDE

DESTDIR = $$QGO_BIN

include(boost.pri)

QMAKE_CXXFLAGS += -std=c++11
# -Wall -Wextra -pedantic -Wshadow -Wpointer-arith -Wcast-align -Wwrite-strings -Wmissing-declarations -Wredundant-decls -Winline -Wno-long-long -Wuninitialized -Wconversion
