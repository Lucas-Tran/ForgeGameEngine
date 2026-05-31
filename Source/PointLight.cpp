#include <PointLight.h>

PointLight::PointLight(
    glm::vec3 position,

    float constant,
    float linear,
    float quadratic,

    glm::vec3 ambient,
    glm::vec3 diffuse,
    glm::vec3 specular
): 
position(position),

constant(constant),
linear(linear),
quadratic(quadratic),

ambient(ambient),
diffuse(diffuse),
specular(specular) {

}

void PointLight::Uniform(ShaderProgram& shaderProgram, std::string uniformString) {
    shaderProgram.SetUniform(uniformString + ".position", position);
    shaderProgram.SetUniform(uniformString + ".constant", constant);
    shaderProgram.SetUniform(uniformString + ".linear", linear);
    shaderProgram.SetUniform(uniformString + ".quadratic", quadratic);
    shaderProgram.SetUniform(uniformString + ".ambient", ambient);
    shaderProgram.SetUniform(uniformString + ".diffuse", diffuse);
    shaderProgram.SetUniform(uniformString + ".specular", specular);
}

void PointLight::SetPosition(glm::vec3 position) {
    this->position = position;
}