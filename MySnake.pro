TEMPLATE = app
CONFIG += console c++11
CONFIG -= app_bundle
CONFIG -= qt

SOURCES += \
        Game.cpp \
        Snake.cpp \
        State.cpp \
        StateFail.cpp \
        StateMenu.cpp \
        StatePlay.cpp \
        main.cpp

LIBS += -L"..\SFML\lib"
LIBS += -L"..\SFML\bin"

CONFIG(release, debug|release): LIBS += -lsfml-audio -lsfml-graphics -lsfml-system -lsfml-network -lsfml-window
CONFIG(debug  , debug|release): LIBS += -lsfml-audio -lsfml-graphics -lsfml-system -lsfml-network -lsfml-window


INCLUDEPATH += "..\SFML\include"
DEPENDPATH += "..\SFML\include"


HEADERS += \
    Game.h \
    Snake.h \
    State.h \
    StateFail.h \
    StateMenu.h \
    StatePlay.h

DISTFILES +=

RESOURCES +=
