#include "opengl.h"

void OpenGl::render() {
    // Koordinatensystem zeichen
    glBegin(GL_LINES);
    glColor3f(1.0f, 0.0f, 0.0f); // X
    glVertex3f(0.0f, 0.0f, 0.0f);
    glVertex4f(1.0f, 0.0f, 0.0f, 0.0f);
    glColor3f(0.0f, 1.0f, 0.0f); // Y
    glVertex3f(0.0f, 0.0f, 0.0f);
    glVertex4f(0.0f, 1.0f, 0.0f, 0.0f);
    glColor3f(0.0f, 0.0f, 1.0f); // Z
    glVertex3f(0.0f, 0.0f, 0.0f);
    glVertex4f(0.0f, 0.0f, 1.0f, 0.0f);
    glEnd();

    // Würfel zeichen
    glPushMatrix();
    glTranslatef(0.0f, 0.0f, -10.0f);
    glColor3f(0.5f, 0.5f, 0.5f);
    for (int i = 0; i < 7; ++i) {
        glBegin(GL_QUADS);
        glVertex3f( 1.0f,-1.0f, 1.0f);
        glVertex3f( 1.0f, 1.0f, 1.0f);
        glVertex3f(-1.0f, 1.0f, 1.0f);
        glVertex3f(-1.0f,-1.0f, 1.0f);
        glEnd();
        if (i < 4)
            glRotatef(90.0f, 0.0f, 1.0f, 0.0f);
        if (i == 4) {
            glRotatef(90.0f, 1.0f, 0.0f, 0.0f);
            glColor3f(1.0f, 0.0f, 0.0f);
        }
        if (i == 5) {
            glRotatef(180.0f, 1.0f, 0.0f, 0.0f);
            glColor3f(0.0f, 1.0f, 0.0f);
        }
    }
    glPopMatrix();

    // Punkt (einfache Demonstration: Color + Vertex)
    glPointSize(10.0f);
    glBegin(GL_POINTS);
    glColor3f(0.0f, 0.0f, 0.0f);
    glVertex3f(0.0f, 0.0f, 0.0f);
    glEnd();
}
