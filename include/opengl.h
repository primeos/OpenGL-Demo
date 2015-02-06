#ifndef OPENGL_H
#define OPENGL_H

#include <stdio.h>
#include <GL/gl.h>

//#define _USE_MATH_DEFINES // for some older plattforms
#include <math.h> // tan()

// for extended printf() format support
#define __STDC_FORMAT_MACROS
#include <inttypes.h>

//#include "assimp_importer.h"
#include "opengl_camera.h"

class OpenGl {
private:
    //AssimpImporter* imp_;
    OpenGlCamera *camera_; // pointer to our camera object
    void render();
public:
    OpenGl();
    ~OpenGl();
    void setupViewport(int width, int height);
    void renderFrame();
};

#endif // OPENGL_H
