TEMPLATE = app
CONFIG += console
CONFIG -= app_bundle
CONFIG -= qt

# Allows us to use C++11 (things like nullptr)
CONFIG += c++11

#Important: you have to copy SDL2.dll from bin to lib in order to make the program work!
win32:LIBS += -L$$PWD/SDL2-2.0.3/i686-w64-mingw32/lib/ -lSDL2 -lSDL2main -mwindows -lopengl32 -lmingw32
win32:INCLUDEPATH += $$PWD/SDL2-2.0.3/i686-w64-mingw32/include $$PWD/glm-0.9.5.4/glm

HEADERS += \
    opengl.h \
    game_window.h \
    opengl_camera.h

SOURCES += main.cpp \
    opengl.cpp \
    game_window.cpp \
    opengl_camera.cpp \
    opengl_camera_cameradata.cpp \
    opengl_render.cpp
