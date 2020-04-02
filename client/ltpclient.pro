# ----------------------------------------------------
# This file is generated by the Qt Visual Studio Add-in.
# ------------------------------------------------------

TEMPLATE = app
TARGET = ltpclient
DESTDIR = ../ltp/Win32/Debug
QT += core gui network xml
CONFIG += debug_and_release
DEFINES += QT_DLL QT_XML_LIB QT_NETWORK_LIB
INCLUDEPATH += ./GeneratedFiles \
    . \
    .. \
    ./GeneratedFiles/Debug
DEPENDPATH += .
QMAKESPEC = linux-arm-gnueabi-g++
QMAKE_CC = arm-linux-gnueabihf-gcc
QMAKE_CXX = arm-linux-gnueabihf-g++
QMAKE_LINK = arm-linux-gnueabihf-gcc
QMAKE_AR = arm-linux-gnueabihf-ar
QMAKE_STRIP = arm-linux-gnueabihf-strip
QMAKE_CXXFLAGS += -std=c++11
QMAKE_CXXFLAGS += -Wno-literal-suffix
QMAKE_CXXFLAGS += -Wno-unused-local-typedefs
QMAKE_CXXFLAGS += -Wall
QMAKE_CXXFLAGS += -Werror
MOC_DIR += ./GeneratedFiles/debug
OBJECTS_DIR += debug
UI_DIR += ./GeneratedFiles
RCC_DIR += ./GeneratedFiles
LIBS += -L. -lstdc++ -lRemoteComm -lm
include(ltpclient.pri)
