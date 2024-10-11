#ifndef SHADER_PROGRAM_H_INCLUDED
#define SHADER_PROGRAM_H_INCLUDED

#include <string>

class ShaderProgram {
public:
    ShaderProgram(const std::string vertexShaderPath, const std::string fragmentShaderPath);

    ~ShaderProgram();

    void Activate() const;

    void SetUniform(const std::string uniformName, int value) const;

    bool Success();
private:
    unsigned int ID;
};

#endif