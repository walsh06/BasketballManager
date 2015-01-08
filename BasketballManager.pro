TEMPLATE = app
CONFIG += console
CONFIG -= app_bundle
CONFIG -= qt
CONFIG += c++11

SOURCES += main.cpp \
    Player.cpp \
    Match.cpp \
    Team.cpp \
    Ball.cpp \
    ProbabilityVector.cpp \
    Heatmap.cpp \
    PositionPointGuard.cpp \
    PositionShootingGuard.cpp \
    PositionSmallForward.cpp \
    PositionPowerForward.cpp \
    PositionCentre.cpp \
    PlayerStrategyShootThree.cpp \
    PlayerStrategyCrashBoards.cpp \
    pugixml.cpp \
    ConsoleGameView.cpp \
    TestGameView.cpp

HEADERS += \
    Player.h \
    Match.h \
    Team.h \
    Ball.h \
    ProbabilityVector.h \
    Heatmap.h \
    PlayerPosition.h \
    PositionPointGuard.h \
    PositionShootingGuard.h \
    PositionSmallForward.h \
    PositionPowerForward.h \
    PositionCentre.h \
    PlayerStrategy.h \
    PlayerStrategyShootThree.h \
    PlayerStrategyCrashBoards.h \
    pugiconfig.hpp \
    pugixml.hpp \
    ConsoleGameView.h \
    GameView.h \
    TestGameView.h

