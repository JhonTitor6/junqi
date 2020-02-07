#-------------------------------------------------
#
# Project created by QtCreator 2019-10-20T16:27:09
#
#-------------------------------------------------

QT       += widgets gui

SOURCES += \
	main.cpp \
	board.cpp \
	stone.cpp \
    singlegame.cpp \
    step.cpp \
    mytimer.cpp \
    gametype.cpp

HEADERS += \
	board.h \
	stone.h \
    singlegame.h \
    step.h \
    mytimer.h \
    gametype.h
TARGET = CCChess
TEMPLATE = app

RC_FILE = junqi.rc
