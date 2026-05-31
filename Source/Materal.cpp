#include <Material.h>

void Material::Uniform(ShaderProgram& shaderProgram, std::string uniformName) {
    diffuseTexture.Uniform(shaderProgram, uniformName + ".diffuseTexture");
    specularTexture.Uniform(shaderProgram, uniformName + ".specularTexture");
    shaderProgram.SetUniform(uniformName + ".shininess", shininess);
}