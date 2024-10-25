#include <ForgeEngine.h>

std::array<ProgramState::Input::Keyboard::Key, 1024> ProgramState::Input::Keyboard::keys;

// Mouse position
float ProgramState::Input::Mouse::mouseX;
float ProgramState::Input::Mouse::mouseY;

// Mouse delta
float ProgramState::Input::Mouse::deltaMouseX;
float ProgramState::Input::Mouse::deltaMouseY;

// Time and delta time
float ProgramState::Time::time;
float ProgramState::Time::deltaTime;