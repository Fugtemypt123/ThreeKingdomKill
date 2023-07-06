QT       += core gui multimedia

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += resources_big

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0
TARGET = ThreeKingdomKill
TEMPLATE = app


SOURCES += \
    cards.cpp \
    choosemenu.cpp \
    endscene.cpp \
    heroes.cpp \
    main.cpp \
    mainwindow.cpp \
    mymenu.cpp \
    mypushbutton.cpp \
    playscene.cpp \
    shapedwindow.cpp

HEADERS += \
    cards.h \
    choosemenu.h \
    endscene.h \
    heroes.h \
    mainwindow.h \
    mymenu.h \
    mypushbutton.h \
    playscene.h \
    shapedwindow.h

FORMS += \
    mainwindow.ui

# Default rules for deployment.


RESOURCES += \
    res.qrc

CONFIG += resources_big
