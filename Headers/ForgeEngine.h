#ifndef FORGE_ENGINE_H_INCLUDED
#define FORGE_ENGINE_H_INCLUDED

#include <array>
#include <GLFW/glfw3.h>

namespace ProgramState {
    namespace Input {
        namespace Keyboard {
            struct Key {
                bool pressed; // Whether the key is pressed
                bool firstPress; // Whether this is the first frame the key is pressed
            };

            // All the keys and their states
            extern std::array<Key, 1024> keys;
        }

        namespace Mouse {
            // Mouse position
            extern float mouseX;
            extern float mouseY;

            // Mouse delta
            extern float deltaMouseX;
            extern float deltaMouseY;
        }
    }

    namespace Time {
        // Time and delta time
        extern float time;
        extern float deltaTime;
    }
}

void UpdateProgramState(GLFWwindow *window);

#endif