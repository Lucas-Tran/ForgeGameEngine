#ifndef MATERIAL_H_INCLUDED
#define MATERIAL_H_INCLUDED

#include <Texture2D.h>
#include <ShaderProgram.h>
#include <string>

struct Material {
    Texture2D diffuseTexture;
    Texture2D specularTexture;
    float shininess;

    void Uniform(ShaderProgram& shaderProgram, std::string uniformName);
};

#endif