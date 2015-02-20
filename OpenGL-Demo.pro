TEMPLATE = app
CONFIG += console
CONFIG -= app_bundle
CONFIG -= qt

# Allows us to use C++11 (things like nullptr)
CONFIG += c++11

#Important: you have to copy SDL2.dll from bin to lib in order to make the program work!
win32:LIBS += -L$$PWD/lib/SDL2-2.0.3/i686-w64-mingw32/lib/ -lSDL2 -lSDL2main -mwindows -lopengl32 -lmingw32
unix:LIBS += -lSDL2 -SDL2main -lGL
win32:INCLUDEPATH += $$PWD/lib/SDL2-2.0.3/i686-w64-mingw32/include $$PWD/lib/glm-0.9.5.4/glm

INCLUDEPATH += include
DEPENDPATH += src

HEADERS += \
    include/game_window.h \
    include/opengl.h \
    include/opengl_camera.h

SOURCES += \
    src/game_window.cpp \
    src/main.cpp \
    src/opengl.cpp \
    src/opengl_camera.cpp \
    src/opengl_camera_cameradata.cpp \
    src/opengl_render.cpp
