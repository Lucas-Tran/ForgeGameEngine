#ifndef SHADER_PROGRAM_H_INCLUDED
#define SHADER_PROGRAM_H_INCLUDED

#include <string>
#include <glm/glm.hpp>

class ShaderProgram {
public:
    ShaderProgram(const std::string vertexShaderPath, const std::string fragmentShaderPath);

    ~ShaderProgram();

    bool Success() const;

    void Activate() const;

    void SetUniform(const std::string uniformName, int value) const;

    void SetUniform(const std::string uniformName, float value) const;

    void SetUniform(const std::string uniformName, glm::vec2 value) const;

    void SetUniform(const std::string uniformName, glm::vec3 value) const;

    void SetUniform(const std::string uniformName, glm::vec4 value) const;
    

    void SetUniform(const std::string uniformName, glm::mat2 value) const;

    void SetUniform(const std::string uniformName, glm::mat3 value) const;

    void SetUniform(const std::string uniformName, glm::mat4 value) const;
private:
    unsigned int ID;
};

#endif