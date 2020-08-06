#-------------------------------------------------
#
# Project created by QtCreator 2020-07-31T17:55:52
#
#-------------------------------------------------

QT       += core gui multimedia

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = CoinFlip
TEMPLATE = app


SOURCES += main.cpp\
        mainscene.cpp \
    mypushbotton.cpp \
    chooselevelscene.cpp \
    playscene.cpp \
    mycoin.cpp \
    dataconfig.cpp

HEADERS  += mainscene.h \
    mypushbotton.h \
    chooselevelscene.h \
    playscene.h \
    mycoin.h \
    dataconfig.h

FORMS    += mainscene.ui

RESOURCES += \
    res.qrc
CONFIG +=c++11
