#include <DirectionalLight.h>

DirectionalLight::DirectionalLight(
    glm::vec3 direction,
    glm::vec3 ambient,
    glm::vec3 diffuse,
    glm::vec3 specular):
    direction(direction),
    ambient(ambient),
    diffuse(diffuse),
    specular(specular) {

}

void DirectionalLight::Uniform(ShaderProgram& shaderProgram, std::string unifornName) {
        shaderProgram.SetUniform(unifornName + ".direction", glm::vec3(0.0f, -1.0f, -1.0f));
        shaderProgram.SetUniform(unifornName + ".ambient", glm::vec3(0.5f, 0.5f, 0.5f));
        shaderProgram.SetUniform(unifornName + ".diffuse", glm::vec3(1.0f, 1.0f, 1.0f));
        shaderProgram.SetUniform(unifornName + ".specular", glm::vec3(1.0f, 1.0f, 1.0f));
}