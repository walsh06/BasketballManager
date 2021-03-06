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
    Tournament.cpp \
    League.cpp \
    LeagueTeam.cpp \
    Manager.cpp \
    pugixml.cpp \
    TournamentMatchup.cpp \
    PlayerGraphic.cpp \
    LeagueScreen.cpp \
    unittests/BallTest.cpp \
    unittests/FoulTest.cpp \
    unittests/PlayerTest.cpp \
    unittests/StatListTest.cpp \
    unittests/TeamTest.cpp \
    Commentary.cpp \
    Analyser.cpp \
    MatchDefenceMan.cpp \
    MatchDefenceZone.cpp \
    MatchDefence.cpp \
    PlayerStrategyDynamic.cpp \
    PlayerStrategyLearning.cpp \
    AutomationTesting.cpp

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
    PlayerStrategyScoringForward.h \
    Tournament.h \
    League.h \
    LeagueTeam.h \
    Manager.h \
    TournamentMatchup.h \
    PlayerGraphic.h \
    LeagueScreen.h \
    Commentary.h \
    Analyser.h \
    MatchDefenceMan.h \
    MatchDefenceZone.h \
    MatchDefence.h \
    PlayerStrategyDynamic.h \
    PlayerStrategyLearning.h \
    AutomationTesting.h


FORMS += \
    MainWindow.ui \
    MatchScreen.ui \
    LeagueScreen.ui




win32:CONFIG(release, debug|release): LIBS += -L$$PWD/../../../../../../usr/src/gtest/release/ -lgtest
else:win32:CONFIG(debug, debug|release): LIBS += -L$$PWD/../../../../../../usr/src/gtest/debug/ -lgtest
else:unix: LIBS += -L$$PWD/../../../../../../usr/src/gtest/ -lgtest

INCLUDEPATH += $$PWD/../../../../../../usr/src/gtest
DEPENDPATH += $$PWD/../../../../../../usr/src/gtest

win32-g++:CONFIG(release, debug|release): PRE_TARGETDEPS += $$PWD/../../../../../../usr/src/gtest/release/libgtest.a
else:win32-g++:CONFIG(debug, debug|release): PRE_TARGETDEPS += $$PWD/../../../../../../usr/src/gtest/debug/libgtest.a
else:win32:!win32-g++:CONFIG(release, debug|release): PRE_TARGETDEPS += $$PWD/../../../../../../usr/src/gtest/release/gtest.lib
else:win32:!win32-g++:CONFIG(debug, debug|release): PRE_TARGETDEPS += $$PWD/../../../../../../usr/src/gtest/debug/gtest.lib
else:unix: PRE_TARGETDEPS += $$PWD/../../../../../../usr/src/gtest/libgtest.a

OTHER_FILES += \
    commentary.xml \
    schedule.xml \
    gameData/commentary.xml \
    gameData/schedule.xml \
    gameData/teams.xml \
    darkorange.stylesheet.txt
