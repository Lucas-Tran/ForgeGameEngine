#ifndef CAMERA_H_INCLUDED
#define CAMERA_H_INCLUDED

#include <glm/glm.hpp>
#include <GLFW/glfw3.h>

class Camera {
public:
    Camera(const glm::vec3 position, const float yaw, const float pitch, const float FOV, const int viewportWidth, const int viewportHeight, const float near, const float far);
    
    void SetProjectionMatrix(const float FOV, const float aspectRatio, const float near, const float far);

    void SetProjectionMatrix(const float FOV, const int viewportWidth, const int viewportHeight, const float near, const float far);

    glm::mat4 GetProjectionMatrix();

    void UpdateDirectionVectors();

    void UpdateViewMatrix();

    glm::mat4 GetViewMatrix();

    void Update();
private:
    // Position
    glm::vec3 position;

    // Rotation
    float yaw;
    float pitch;

    // Direction vectors
    glm::vec3 right;
    glm::vec3 up;
    glm::vec3 forward;

    // Matrices
    glm::mat4 viewMatrix;
    glm::mat4 projectionMatrix;
};

#endif