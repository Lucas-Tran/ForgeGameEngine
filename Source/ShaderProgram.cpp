#include <ShaderProgram.h>

#include <iostream>
#include <fstream>
#include <sstream>
#include <glad/glad.h>

#include <glm/gtc/type_ptr.hpp>

std::string ReadFileContents(const std::string path) {
    // Create a filestream for the desired file
    std::ifstream fileStream(path);

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

    // Check for errors
    int sucess;
    glGetShaderiv(shader, GL_COMPILE_STATUS, &sucess);

    if (!sucess) {
        // Get the shader info log and print out the error. Returning 0 means that it failed.
        char infoLog[512];
        glGetShaderInfoLog(shader, 512, nullptr, infoLog);
        std::string type = (shaderType == GL_VERTEX_SHADER) ? "VERTEX" : "FRAGMENT";
        std::cout << "ERROR::SHADER::" << type << "::COMPILATION::FAILED: " << shaderPath << std::endl;
        std::cout << infoLog << std::endl;
        return 0;
    }

    // Return the compiled shader
    return shader;
}

ShaderProgram::ShaderProgram(const std::string vertexShaderPath, const std::string fragmentShaderPath) {
    // Create and compile the vertex shader
    unsigned int vertexShader = CompileShader(vertexShaderPath, GL_VERTEX_SHADER);

    // Create and compile the fragment shader
    unsigned int fragmentShader = CompileShader(fragmentShaderPath, GL_FRAGMENT_SHADER);

    // Check if there are any errors
    if (vertexShader == 0 || fragmentShader == 0) {
        ID = 0;
        return;
    }

    // Create the program
    ID = glCreateProgram();

    // Attatch shaders to program and link it
    glAttachShader(ID, vertexShader);
    glAttachShader(ID, fragmentShader);
    glLinkProgram(ID);

    int success;
    glGetProgramiv(ID, GL_LINK_STATUS, &success);
    if (!success) {
        char infoLog[512];
        glGetProgramInfoLog(ID, 512, nullptr, infoLog);
        std::cout << "ERROR::SHADER::PROGRAM::LINKING::FAILED" << std::endl;
        std::cout << infoLog << std::endl;
        ID = 0;
        return;
    }

    // Delete the shaders since they are no longer in the program
    glDeleteShader(vertexShader);
    glDeleteShader(fragmentShader);
}

ShaderProgram::~ShaderProgram() {
    // Once the object is deleted, we also have to delete the program stored in OpenGL
    glDeleteProgram(ID);
}

bool ShaderProgram::Success() const {
    return ID != 0;
}

void ShaderProgram::Activate() const {
    // A method for activating the shader program
    glUseProgram(ID);
}

// For these functions, we get the uniform location using the program ID and the uniform name and set it to our value
    
void ShaderProgram::SetUniform(const std::string uniformName, int value) const {
    glUniform1i(glGetUniformLocation(ID, uniformName.c_str()), value);
}

void ShaderProgram::SetUniform(const std::string uniformName, float value) const {
    glUniform1f(glGetUniformLocation(ID, uniformName.c_str()), value);
}

// For these functions, we use "type_ptr" because these accept the pointers to arrays of values

void ShaderProgram::SetUniform(const std::string uniformName, glm::vec2 value) const {
    glUniform2fv(glGetUniformLocation(ID, uniformName.c_str()), 1, glm::value_ptr(value));
}

void ShaderProgram::SetUniform(const std::string uniformName, glm::vec3 value) const {
    glUniform3fv(glGetUniformLocation(ID, uniformName.c_str()), 1, glm::value_ptr(value));
}

void ShaderProgram::SetUniform(const std::string uniformName, glm::vec4 value) const {
    glUniform4fv(glGetUniformLocation(ID, uniformName.c_str()), 1, glm::value_ptr(value));
}


void ShaderProgram::SetUniform(const std::string uniformName, glm::mat2 value) const {
    glUniformMatrix2fv(glGetUniformLocation(ID, uniformName.c_str()), 1, false, glm::value_ptr(value));
}

void ShaderProgram::SetUniform(const std::string uniformName, glm::mat3 value) const {
    glUniformMatrix3fv(glGetUniformLocation(ID, uniformName.c_str()), 1, false, glm::value_ptr(value));
}

void ShaderProgram::SetUniform(const std::string uniformName, glm::mat4 value) const {
    glUniformMatrix4fv(glGetUniformLocation(ID, uniformName.c_str()), 1, false, glm::value_ptr(value));
}