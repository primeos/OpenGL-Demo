#ifndef OPENGL_CAMERA_H
#define OPENGL_CAMERA_H

#include <stdio.h>
#include <SDL2/SDL.h>
#include <GL/gl.h>

#define GLM_FORCE_RADIANS
#include <glm/glm.hpp>
#include <glm/gtc/type_ptr.hpp>
//#include <glm/gtc/quaternion.hpp>
#include <glm/gtc/matrix_transform.hpp>

//#include <glm/mat4x4.hpp>
//#include <glm/vec3.hpp>
#include <glm/gtx/euler_angles.hpp>
#include <glm/gtx/rotate_vector.hpp>

enum CameraMovement {
    FORWARD, BACKWARD, LEFT, RIGHT, UP, DOWN
};

class OpenGlCamera
{
private:
    struct CameraData {
        CameraData();
        void ResetCamera();
        void ApplyCamera();
        void SetViewport(int width, int height);
        void SetPos(float x, float y, float z);
        void AddPos(float x, float y, float z);
        void SetRot(float pitch, float yaw, float roll);
        void AddRot(float pitch, float yaw, float roll);
        float camera_speed;
        float camera_sensitivity;
        float camera_zoom;
        glm::vec3 camera_up;
        glm::vec3 camera_position;
        glm::vec3 camera_rotation;
        float fov;
        int viewport[2];
        float clipping[2];
    };
    CameraData *camera_data_; // stores our camera data
    Uint64 last_call_time_;
public:
    OpenGlCamera();
    ~OpenGlCamera();
    void ResetCamera();
    void SetViewport(int width, int height);
    void SetCamera(float x, float y, float z, float pitch, float yaw, float roll);
    void UpdateCamera(const Uint8 *keyboard_state, int *x, int*y);
    void ApplyCamera();
};

#endif // OPENGL_CAMERA_H
