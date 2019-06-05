QT       += core gui multimedia

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = arkanoid
TEMPLATE = app


SOURCES += main.cpp\
        mainwindow.cpp \
    dialog.cpp \
    cube.cpp \
    game.cpp \
    ball.cpp \
    racket.cpp \
    score.cpp \
    lives.cpp \
    border.cpp

HEADERS  += mainwindow.h \
    dialog.h \
    cube.h \
    game.h \
    ball.h \
    racket.h \
    score.h \
    lives.h \
    border.h

FORMS    += mainwindow.ui \
    dialog.ui

RESOURCES += \
    img.qrc \
    sounds.qrc

DISTFILES +=
