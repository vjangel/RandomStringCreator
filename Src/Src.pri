QT          += core gui network
greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

INCLUDEPATH += $$PWD

HEADERS     += \

SOURCES     += \ 
    $$PWD/main.cpp

RESOURCES   += \
    $$PWD/../Resource/Resource.qrc

include($$PWD/Universal/Universal.pri)
include($$PWD/MainWidget/MainWidget.pri)
# include($$PWD/SingleApplication/SingleApplication.pri)