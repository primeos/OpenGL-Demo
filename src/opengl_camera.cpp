#include "opengl_camera.h"

OpenGlCamera::OpenGlCamera() {
    camera_data_ = new CameraData();
    last_call_time_ = SDL_GetPerformanceCounter();
}

OpenGlCamera::~OpenGlCamera() {
    delete camera_data_;
    camera_data_ = nullptr;
}

void OpenGlCamera::ResetCamera() {
    this->camera_data_->ResetCamera();
}

void OpenGlCamera::SetViewport(int width, int height) {
    this->camera_data_->SetViewport(width, height);
}

void OpenGlCamera::SetCamera(float x, float y, float z, float pitch, float yaw, float roll) {
    this->camera_data_->SetPos(x, y, z);
    this->camera_data_->SetRot(pitch, yaw, roll);
}

void OpenGlCamera::UpdateCamera(const Uint8 *keyboard_state, int *x, int *y) {
    double render_time = (SDL_GetPerformanceCounter() - last_call_time_) / (double)SDL_GetPerformanceFrequency();
    last_call_time_ = SDL_GetPerformanceCounter();

    // the mouse movement doesn't depend on the render_time (fps)
    this->camera_data_->AddRot((-*y) * 0.001f * this->camera_data_->camera_sensitivity, (-*x) * 0.001f * this->camera_data_->camera_sensitivity, 0.0f);

    /*if (keyboard_state[SDL_SCANCODE_Q])
        this->camera_data->AddRot(0.0f, 0.0f, +render_time * this->camera_data_->speed * 0.1f);
    if (keyboard_state[SDL_SCANCODE_E])
        this->camera_data->AddRot(0.0f, 0.0f, -render_time * this->camera_data_->speed * 0.1f);*/

    // Movement
    if (keyboard_state[SDL_SCANCODE_Q])
        this->camera_data_->AddPos(0.0f, 0.0f, -render_time * this->camera_data_->camera_speed);
    if (keyboard_state[SDL_SCANCODE_E])
        this->camera_data_->AddPos(0.0f, 0.0f, +render_time * this->camera_data_->camera_speed);

    if (keyboard_state[SDL_SCANCODE_W] || keyboard_state[SDL_SCANCODE_UP])
        this->camera_data_->AddPos(+render_time * this->camera_data_->camera_speed, 0.0f, 0.0f);
    if (keyboard_state[SDL_SCANCODE_A] || keyboard_state[SDL_SCANCODE_LEFT])
        this->camera_data_->AddPos(0.0f, +render_time * this->camera_data_->camera_speed, 0.0f);
    if (keyboard_state[SDL_SCANCODE_S] || keyboard_state[SDL_SCANCODE_DOWN])
        this->camera_data_->AddPos(-render_time * this->camera_data_->camera_speed, 0.0f, 0.0f);
    if (keyboard_state[SDL_SCANCODE_D] || keyboard_state[SDL_SCANCODE_RIGHT])
        this->camera_data_->AddPos(0.0f, -render_time * this->camera_data_->camera_speed, 0.0f);
}

void OpenGlCamera::ApplyCamera() {
    this->camera_data_->ApplyCamera();
}
