#include "game_window.h"

GameWindow::GameWindow(int width, int height, bool fullscreen) {
    printf("Creating game window.\n");
    // Initialize the SDL video subsystem
    if (SDL_Init(SDL_INIT_VIDEO) < 0)
        fprintf(stderr, "ERROR: Unable to initialize SDL!\n");

    // Gives us more control
    SDL_GL_SetAttribute( SDL_GL_RED_SIZE, 5 ); // 8
    SDL_GL_SetAttribute( SDL_GL_GREEN_SIZE, 5 ); // 8
    SDL_GL_SetAttribute( SDL_GL_BLUE_SIZE, 5 ); // 8
    SDL_GL_SetAttribute( SDL_GL_DEPTH_SIZE, 16 ); // 24
    SDL_GL_SetAttribute( SDL_GL_DOUBLEBUFFER, 1 ); // 1

    // Must be set before context creation
    //SDL_GL_SetAttribute(SDL_GL_CONTEXT_PROFILE_MASK, SDL_GL_CONTEXT_PROFILE_CORE); // deprecated functions are disabled
    //SDL_GL_SetAttribute(SDL_GL_CONTEXT_PROFILE_MASK, SDL_GL_CONTEXT_PROFILE_ES); // mobile
    //SDL_GL_SetAttribute( SDL_GL_CONTEXT_MAJOR_VERSION, 3 );
    //SDL_GL_SetAttribute( SDL_GL_CONTEXT_MINOR_VERSION, 2 );

    // Fullscreen anti-aliasing
    //SDL_GL_SetAttribute( SDL_GL_MULTISAMPLEBUFFERS, 1 );
    //SDL_GL_SetAttribute( SDL_GL_MULTISAMPLESAMPLES, 4 );

    // Create the window
    // SDL_WINDOW_FULLSCREEN(_DESKTOP) with DESKTOP it doesn't change the resolution
    // SDL_WINDOWPOS_CENTERED is also a good choice
    if (!fullscreen) // fullscreen == false
        sdl_window_ = SDL_CreateWindow("OpenGL-Demo",
                                               SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED,
                                               width, height,
                                               SDL_WINDOW_OPENGL);
    else
        sdl_window_ = SDL_CreateWindow("OpenGL-Demo",
                                               SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED,
                                               width, height,
                                               SDL_WINDOW_OPENGL | SDL_WINDOW_FULLSCREEN_DESKTOP);

    if (!sdl_window_)
        fprintf(stderr, "ERROR: Couldn't create the SDL window: %s\n", SDL_GetError());

    // Create the OpenGL context
    gl_context_ = SDL_GL_CreateContext(sdl_window_);
    if (!gl_context_) // gl_context == NULL
        fprintf(stderr, "ERROR: Couldn't create the OpenGL context: %s\n", SDL_GetError());

    //SDL_GL_SetAttribute();
    //SDL_GL_SetSwapInterval(); // can be changed on an existing context
    //SDL_SetWindowFullscreen(); // toggle fullscreen without loosing the gl context

    // Good FPS-Settings:
    if (SDL_SetRelativeMouseMode(SDL_TRUE) < 0) // you can't close the window
        fprintf(stderr, "ERROR: Couldn't apply the relative mouse mode: %s\n", SDL_GetError());

    // Create an object from our OpenGL class
    opengl_ = new OpenGl();

    // Set our viewport size
    int w, h;
    SDL_GetWindowSize(sdl_window_, &w, &h);
    opengl_->setupViewport(w, h); // ! Fullscreen

    // Enter the main loop
    mainLoop();
}

GameWindow::~GameWindow() {
    // Cleaning up

    delete opengl_;
    opengl_ = nullptr;

    printf("Destroying game window.\n");
    SDL_GL_DeleteContext(gl_context_);
    SDL_DestroyWindow(sdl_window_);
}

void GameWindow::mainLoop() {
    bool bExit = false;
    while (!bExit) {
        SDL_Event event;
        while (SDL_PollEvent(&event)) { // not thead save; calls SDL_PumpEvents(); call only from main/video-init thread
            if (event.type == SDL_QUIT)
                bExit = true;
            if (event.type == SDL_KEYDOWN && event.key.keysym.sym == SDLK_ESCAPE)
                bExit = true;
            if (event.type == SDL_WINDOWEVENT && event.window.event == SDL_WINDOWEVENT_CLOSE)
                bExit = true;
            if (event.type == SDL_KEYDOWN && event.key.keysym.sym == SDLK_F10) {
                toggleFullscreen();
            }
        }
        // render the next frame and swap the buffers
        opengl_->renderFrame();
        SDL_GL_SwapWindow(sdl_window_);
        //Sleep(5); // to get lower fps
    }
    printf("Terminating...\n");
}

void GameWindow::toggleFullscreen() {
    if (SDL_GetWindowFlags(sdl_window_) & SDL_WINDOW_FULLSCREEN_DESKTOP) {
        if (SDL_SetWindowFullscreen(sdl_window_, 0) < 0) // 0 disables fullscreen
            fprintf(stderr, "ERROR: Couldn't change the fullscreen state: %s\n", SDL_GetError());
    }
    else {
        if (SDL_SetWindowFullscreen(sdl_window_, SDL_WINDOW_FULLSCREEN_DESKTOP) < 0)
            fprintf(stderr, "ERROR: Couldn't change the fullscreen state: %s\n", SDL_GetError());
    }
    // Update our viewport size
    int w, h;
    SDL_GetWindowSize(sdl_window_, &w, &h);
    opengl_->setupViewport(w, h); // ! Fullscreen

}
