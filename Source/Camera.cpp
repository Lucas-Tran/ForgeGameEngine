#include <Camera.h>

#include <ForgeEngine.h>
using namespace ProgramState;

#include <glm/gtc/matrix_transform.hpp>

#include <iostream>

const float SPEED = 5.0f;
const float SENSITIVITY = 1.0f;

Camera::Camera(const glm::vec3 position, const float yaw, const float pitch, const float FOV, const int viewportWidth, const int viewportHeight, const float near, const float far): position(position), yaw(yaw), pitch(pitch) {
    SetProjectionMatrix(FOV, viewportWidth, viewportHeight, near, far);
}

void Camera::SetProjectionMatrix(const float FOV, const float aspectRatio, const float near, const float far) {
    projectionMatrix = glm::perspective(glm::radians(FOV), aspectRatio, near, far);
}

void Camera::SetProjectionMatrix(const float FOV, const int viewportWidth, const int viewportHeight, const float near, const float far) {
    SetProjectionMatrix(FOV, (float)viewportWidth / viewportHeight, near, far);
}

glm::mat4 Camera::GetProjectionMatrix() {
    return projectionMatrix;
}

void Camera::UpdateDirectionVectors() {
    const float yaw = glm::radians(this->yaw);
    const float pitch = glm::radians(this->pitch);

    forward.x = -sin(yaw) * cos(pitch);
    forward.y = sin(pitch);
    forward.z = -cos(yaw) * cos(pitch);

    right = glm::normalize(glm::cross(forward, glm::vec3(0.0f, 1.0f, 0.0f)));
    up = glm::cross(right, forward);
}

void Camera::UpdateViewMatrix() {
    viewMatrix = glm::inverse(glm::mat4(glm::vec4(right, 0.0f), glm::vec4(up, 0.0f), glm::vec4(-forward, 0.0f), glm::vec4(position, 1.0f)));
}

glm::mat4 Camera::GetViewMatrix() {
    return viewMatrix;
}

void Camera::Update() {
    yaw -= Input::Mouse::deltaMouseX * SENSITIVITY;
    pitch += Input::Mouse::deltaMouseY * SENSITIVITY;
    if (pitch > 89.0f) {
        pitch = 89.0f;
    } else if (pitch < -89.0f) {
        pitch = -89.0f;
    }
    
    UpdateDirectionVectors();


    const float speed = SPEED * Time::deltaTime;
    if (Input::Keyboard::keys[GLFW_KEY_W].pressed) {
        position += forward * speed;
    }
    std::cout << 5 * Time::deltaTime << std::endl;
    if (Input::Keyboard::keys[GLFW_KEY_S].pressed) {
        position -= forward * speed;
    }
    if (Input::Keyboard::keys[GLFW_KEY_Q].pressed) {
        position -= up * speed;
    }
    if (Input::Keyboard::keys[GLFW_KEY_E].pressed) {
        position += up * speed;
    }
    if (Input::Keyboard::keys[GLFW_KEY_A].pressed) {
        position -= right * speed;
    }
    if (Input::Keyboard::keys[GLFW_KEY_D].pressed) {
        position += right * speed;
    }

    UpdateViewMatrix();
}