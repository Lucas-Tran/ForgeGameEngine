# Forge Engine


## Installation

1. You need to download CMake. To do so, go to the this website to download [CMake](https://cmake.org/download/).

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

Version 0.2 - Added color to the window by using GLAD
Version 0.1 - Created basic window program