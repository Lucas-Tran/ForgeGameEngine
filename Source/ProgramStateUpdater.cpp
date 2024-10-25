#include <ForgeEngine.h>

using namespace ProgramState;

bool firstFrame = true;

void UpdateProgramState(GLFWwindow *window) {
    // Time
    float previousTime = Time::time;
    Time::time = glfwGetTime();
    Time::deltaTime = firstFrame ? 0 : (Time::time - previousTime);
    
    // Mouse position
    float previousMouseX = Input::Mouse::mouseX;
    float previousMouseY = Input::Mouse::mouseY;
    double outputMouseX, outputMouseY;
    glfwGetCursorPos(window, &outputMouseX, &outputMouseY);
    Input::Mouse::mouseX = outputMouseX;
    Input::Mouse::mouseY = -outputMouseY;
    Input::Mouse::deltaMouseX = firstFrame ? 0 : (Input::Mouse::mouseX - previousMouseX);
    Input::Mouse::deltaMouseY = firstFrame ? 0 : (Input::Mouse::mouseY - previousMouseY);

    // Keys
    for (unsigned int i = 0; i < 1024; i++) {
        Input::Keyboard::keys[i].pressed = glfwGetKey(window, i) == GLFW_PRESS;
    }

    firstFrame = false;
}