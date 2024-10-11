#include <ShaderProgram.h>

#include <iostream>
#include <fstream>
#include <sstream>
#include <glad/glad.h>

std::string ReadFileContents(const std::string path) {
    // Create a filestream for the desired file
    std::ifstream fileStream("Resources/" + path);

    // Create a stringstream to read the file buffer contents
    std::ostringstream stringStream;
    stringStream << fileStream.rdbuf();

    // Return the string version of the stringstream we just used to read file contents
    return stringStream.str();
}

unsigned int CompileShader(const std::string shaderPath, unsigned int shaderType) {
    // Get the shader source by reading the file contents of the shader path and converting it to a C-String to work with OpenGL
    std::string shaderSource = ReadFileContents(shaderPath);
    const char *source = shaderSource.c_str();

    // Create the shader and compile it with the shader source
    const unsigned int shader = glCreateShader(shaderType);
    glShaderSource(shader, 1, &source, nullptr);
    glCompileShader(shader);

    // Return the compiled shader
    return shader;
}

ShaderProgram::ShaderProgram(const std::string vertexShaderPath, const std::string fragmentShaderPath): ID(glCreateProgram()) /*    The ID is going to be the ID of a new program   */ {
    // Create and compile the vertex shader
    unsigned int vertexShader = CompileShader(vertexShaderPath, GL_VERTEX_SHADER);

    // Create and compile the fragment shader
    unsigned int fragmentShader = CompileShader(fragmentShaderPath, GL_FRAGMENT_SHADER);

    // Attatch shaders to program and link it
    glAttachShader(ID, vertexShader);
    glAttachShader(ID, fragmentShader);
    glLinkProgram(ID);

    // Delete the shaders since they are no longer in the program
    glDeleteShader(vertexShader);
    glDeleteShader(fragmentShader);
}

ShaderProgram::~ShaderProgram() {
    // Once the object is deleted, we also have to delete the program stored in OpenGL
    glDeleteProgram(ID);
}

void ShaderProgram::Activate() const {
    // A method for activating the shader program
    glUseProgram(ID);
}