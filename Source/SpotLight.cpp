#include <SpotLight.h>

SpotLight::SpotLight(
    glm::vec3 position,
    glm::vec3 forward,

    float cutOffAngle,
    float outerCutOffAngle,

    float constant,
    float linear,
    float quadratic,

    glm::vec3 ambient,
    glm::vec3 diffuse,
    glm::vec3 specular
):
position(position),
forward(forward),
cutOffAngle(cutOffAngle),
outerCutOffAngle(outerCutOffAngle),
constant(constant),
linear(linear),
quadratic(quadratic),
ambient(ambient),
diffuse(diffuse),
specular(specular) {

}

void SpotLight::Uniform(ShaderProgram& shaderProgram, std::string uniformName) {

    // Position and forward
    shaderProgram.SetUniform(uniformName + ".position", position);
    shaderProgram.SetUniform(uniformName + ".direction", forward);

    // Angle restrictions (Pre-compute the cosines!)
    shaderProgram.SetUniform(uniformName + ".cutOff", glm::cos(glm::radians(cutOffAngle)));
    shaderProgram.SetUniform(uniformName + ".outerCutOff", glm::cos(glm::radians(outerCutOffAngle)));

    // Set attenuation and light colors
    shaderProgram.SetUniform(uniformName + ".constant", constant);
    shaderProgram.SetUniform(uniformName + ".linear", linear);
    shaderProgram.SetUniform(uniformName + ".quadratic", quadratic);;

    // 3. ESSENTIAL SPOTLIGHT COLORS
    shaderProgram.SetUniform(uniformName + ".ambient", ambient); 
    shaderProgram.SetUniform(uniformName + ".diffuse", diffuse);
    shaderProgram.SetUniform(uniformName + ".specular", specular);
}

void SpotLight::SetPosition(glm::vec3 position) {
    this->position = position;
}

void SpotLight::SetForward(glm::vec3 forward) {
    this->forward = forward;
}