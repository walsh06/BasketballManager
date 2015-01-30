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
    StatList.cpp \
    PlayerStrategyInsideOutside.cpp \
    PlayerStrategyOutsidePlaymaker.cpp \
    PlayerStrategyInsidePlaymaker.cpp \
    PlayerStrategyPostScorer.cpp \
    PlayerStrategyBalancedPlaymaker.cpp \
    PlayerStrategyBalanced.cpp \
    pugixml.cpp \
    Fouls.cpp \
    PlayerStrategyScoringForward.cpp \
    Tournament.cpp \
    League.cpp \
    LeagueTeam.cpp
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
    Fouls.h \
    PlayerStrategyScoringForward.h \
    Tournament.h \
    League.h \
    LeagueTeam.h

