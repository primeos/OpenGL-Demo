#ifndef GAME_WINDOW_H
#define GAME_WINDOW_H

#include <stdio.h>
#include <SDL2/SDL.h>

#include "opengl.h"

class GameWindow
{
private:
    SDL_Window *sdl_window_; // our SDL window
    SDL_GLContext gl_context_; // our OpenGL context
    OpenGl *opengl_; // pointer to an object from our OpenGL class
    void mainLoop();
    void toggleFullscreen();
public:
    GameWindow(int width, int height, bool fullscreen);
    ~GameWindow();
};

#endif // GAME_WINDOW_H
