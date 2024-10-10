cd glfw-3.4
mkdir Build
cmake -S . -B Build
cmake --build Build
cd ..
mv glfw-3.4/Build/src/libglfw3.* Dependencies/Libraries
rm -r glfw-3.4
rm BuildGLFW.sh