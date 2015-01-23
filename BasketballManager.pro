TEMPLATE = app

CONFIG += c++11
CONFIG -= console
greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

QT       += sql
QT       += core gui

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
    StatList.cpp \
    PlayerStrategyInsideOutside.cpp \
    PlayerStrategyOutsidePlaymaker.cpp \
    PlayerStrategyInsidePlaymaker.cpp \
    MainWindow.cpp \
    MatchScreen.cpp \
    MatchReceiver.cpp \
    PlayerStrategyPostScorer.cpp \
    PlayerStrategyBalancedPlaymaker.cpp \
    PlayerStrategyBalanced.cpp \
    Fouls.cpp \
    PlayerStrategyScoringForward.cpp \
    pugixml.cpp

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
    StatList.h \
    PlayerStrategyInsideOutside.h \
    PlayerStrategyOutsidePlaymaker.h \
    PlayerStrategyInsidePlaymaker.h \
    PlayerStrategyPostScorer.h \
    PlayerStrategyBalancedPlaymaker.h \
    PlayerStrategyBalanced.h \
    pugiconfig.hpp \
    pugixml.hpp \
    MainWindow.h \
    MatchScreen.h \
    MatchReceiver.h \
    Fouls.h \
    PlayerStrategyScoringForward.h

FORMS += \
    MainWindow.ui \
    MatchScreen.ui



