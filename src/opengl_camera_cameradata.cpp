#include <opengl_camera.h>

OpenGlCamera::CameraData::CameraData() {
    camera_sensitivity = 2.5f;
    camera_speed = 7.5f;
    camera_zoom = 1.0f;
    SetPos(0.0f, 0.0f, 0.0f);
    SetRot(0.0f, 0.0f, 0.0f);
    fov = 70.0f;
    viewport[0] = 0; // default values - we'll update them later
    viewport[1] = 0;
    clipping[0] = 0.1f;
    clipping[1] = 100.0f;
}

void OpenGlCamera::CameraData::ResetCamera() {
    camera_sensitivity = 2.5f;
    camera_speed = 7.5f;
    camera_zoom = 1.0f;
    SetPos(0.0f, 0.0f, 0.0f);
    SetRot(0.0f, 0.0f, 0.0f);
    fov = 70.0f;
    viewport[0] = 0; // default values - we'll update them later
    viewport[1] = 0;
    clipping[0] = 0.1f;
    clipping[1] = 100.0f;
}

void OpenGlCamera::CameraData::ApplyCamera() {
    if (viewport[0] == 0 && viewport[1] == 0)
        fprintf(stderr, "ERROR: Viewport resolution not passed to the camera!\n");
    if (viewport[1] == 0)
        viewport[1] = 1;
    glm::mat4 projection = glm::perspective(fov * camera_zoom, (viewport[0] / (float)viewport[1]), clipping[0], clipping[1]);

    glm::vec3 rotation_v = glm::vec3(0.0f, 0.0f, -1.0f);
    rotation_v = glm::rotateX(rotation_v, camera_rotation.x);
    rotation_v = glm::rotateY(rotation_v, camera_rotation.y);
    glm::mat4 view = glm::lookAt(camera_position, camera_position + rotation_v, camera_up);

    //glMatrixMode(GL_PROJECTION);
    //glLoadIdentity();
    //glm::mat4 mvp = projection * view; // modelview-projection
    //glLoadMatrixf(glm::value_ptr(mvp));

    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    glLoadMatrixf(glm::value_ptr(projection));

    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
    glLoadMatrixf(glm::value_ptr(view));
}

void OpenGlCamera::CameraData::SetViewport(int width, int height) {
    viewport[0] = width;
    viewport[1] = height;
}

void OpenGlCamera::CameraData::SetPos(float x, float y, float z) {
    camera_position.x = x;
    camera_position.y = y;
    camera_position.z = z;
}

void OpenGlCamera::CameraData::AddPos(float forward, float left, float up) {
    glm::vec3 rotation_v = glm::vec3(0.0f, 0.0f, -1.0f);
    rotation_v = glm::rotateX(rotation_v, camera_rotation.x);
    rotation_v = glm::rotateY(rotation_v, camera_rotation.y);

    camera_position += rotation_v * forward;
    camera_position += glm::normalize(glm::cross(camera_up, rotation_v)) * left;
    camera_position += camera_up * up;
}

void OpenGlCamera::CameraData::SetRot(float pitch, float yaw, float roll) {
    camera_rotation = glm::vec3(0.0f, 0.0f, 0.0f);
    AddRot(pitch, yaw, roll);
}

void OpenGlCamera::CameraData::AddRot(float pitch, float yaw, float roll) {
    if (!(camera_rotation.x + pitch < -1.5f || camera_rotation.x + pitch > 1.5f))
        camera_rotation.x += pitch;

    camera_rotation.y += yaw;

    camera_up = glm::vec3(0.0f, 1.0f, 0.0f);

    // 2DO: implement rotation
    camera_rotation.z += roll;
}
