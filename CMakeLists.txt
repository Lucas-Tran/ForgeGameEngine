cmake_minimum_required(VERSION 3.5.0)
project(ForgeEngine VERSION 0.4 LANGUAGES C CXX)

set(CMAKE_C_STANDARD 17)
set(CMAKE_CXX_STANDARD 20)


include_directories(${CMAKE_SOURCE_DIR}/Dependencies/Include)
link_directories(${CMAKE_SOURCE_DIR}/Dependencies/Libraries)

file(GLOB_RECURSE SOURCE_FILES ${CMAKE_SOURCE_DIR}/Source/*.cpp ${CMAKE_SOURCE_DIR}/Source/*.c)

add_executable(${CMAKE_PROJECT_NAME} ${SOURCE_FILES})

find_package(OpenGL REQUIRED)

target_link_libraries(${CMAKE_PROJECT_NAME} glfw3 ${OPENGL_LIBRARIES})

if (APPLE)
    target_link_libraries(${CMAKE_PROJECT_NAME} "-framework Cocoa" "-framework IOKit")
endif()