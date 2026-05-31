#ifndef SPOT_LIGHT_H_INCLUDED
#define SPOT_LIGHT_H_INCLUDED

#include <glm/glm.hpp>
#include <string>
#include <ShaderProgram.h>

class SpotLight {
public:
SpotLight(
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
);

void Uniform(ShaderProgram& shaderProgram, std::string uniformName);

void SetPosition(glm::vec3 position);

void SetForward(glm::vec3 forward);

private:
    glm::vec3 position;
    glm::vec3 forward;

    float cutOffAngle;
    float outerCutOffAngle;

    float constant;
    float linear;
    float quadratic;

    glm::vec3 ambient;
    glm::vec3 diffuse;
    glm::vec3 specular;
};

#endif