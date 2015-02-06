#include "opengl.h"

OpenGl::OpenGl() {
    printf("Initializing OpenGL.\n");
    glShadeModel(GL_SMOOTH);
    glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
    glClearDepth(1.0f);
    glEnable(GL_DEPTH_TEST);
    glDepthFunc(GL_LEQUAL);
    glHint(GL_PERSPECTIVE_CORRECTION_HINT, GL_NICEST);

    /* Optional: Backface Culling
    glCullFace( GL_BACK );
    glFrontFace( GL_CCW );
    glEnable( GL_CULL_FACE );
    */

    // Init our importer and load the scene
    //imp_ = new AssimpImporter();
    //imp_->LoadDefaultScene();

    // Create our camera
    camera_ = new OpenGlCamera();

    // the performance timer resolution is OS dependent
    printf("Performance timer resolution: %" PRIu64 " Ticks / Second\n", SDL_GetPerformanceFrequency());
}

OpenGl::~OpenGl() {
    //delete imp_;
    //imp_ = nullptr;
    delete camera_;
    camera_ = nullptr;
    printf("Deactivating OpenGL.\n");
}

void OpenGl::setupViewport(int width, int height) {
    if (height == 0)
        height = 1;

    // Setup our viewport.
    glViewport(0, 0, (GLsizei)width, (GLsizei)height);

    // Update our camera object (aspect ratio)
    camera_->SetViewport(width, height);
    camera_->ApplyCamera();
}

void OpenGl::renderFrame() {
    // Update our camera with user input
    int x, y;
    SDL_GetRelativeMouseState(&x, &y);
    camera_->UpdateCamera(SDL_GetKeyboardState(NULL), &x, &y);
    camera_->ApplyCamera();

    glClearColor( 1.0f, 1.0f, 1.0f, 1.0f ); // Set the background color
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT); // Clear the screen and the depth buffer

    render();
}
