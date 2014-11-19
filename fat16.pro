TEMPLATE = app
CONFIG += console
CONFIG -= app_bundle
CONFIG -= qt

QMAKE_CXXFLAGS += -std=c++11

SOURCES += main.cpp \
    fat.cpp \
    file.cpp \
    directory_table.cpp

include(deployment.pri)
qtcAddDeployment()

HEADERS += \
    fat.h \
    file.h \
    directory_table.h

