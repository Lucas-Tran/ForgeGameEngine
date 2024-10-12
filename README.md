# Forge Engine


## Installation

1. You need to download CMake if you have not done so. To do so, go to the this website to download [CMake](https://cmake.org/download/).

2. Launch CMake, then go to "Tools > How to Install For Command Line Use" and chose your way to install CMake for the command line.

## Building GLFW into a library

To avoid having to explain the entire process of building GLFW, I created a shell script to do just that. Just type "./BuildGLFW.sh" and you are done building it.

## Building The Project

Now we can start to build the main project itself!!!

### Configure the build

1. Make a folder named "Build"

2. Type the "cmake -S . -B Build" in the command line interface

### Build & run

1. Once you have [configured the build](###configure-the-build) it is time to build it. Type "cmake --build Build" in the command line interface.

2. After that, go into the "Build" folder and run the executable.

## Change Log

Version 0.9 - Made a first person controller
Version 0.8 - Made a cube
Version 0.7 - Added 3D projection and made the quad spinning
Version 0.6 - Added textures and shader errors
Version 0.5 - Abstracted OpenGL into classes
Version 0.4 - Used an element buffer to display a quad
Version 0.3 - Made a triangle appear on the window
Version 0.2 - Added color to the window by using GLAD
Version 0.1 - Created basic window program