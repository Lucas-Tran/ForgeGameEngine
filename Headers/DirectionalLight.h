#ifndef DIRECTIONAL_LIGHT_H_INCLUDED
#define DIRECTIONAL_LIGHT_H_INCLUDED

#include <glm/glm.hpp>
#include <string>
#include <ShaderProgram.h>

class DirectionalLight {
public:

    DirectionalLight(
    glm::vec3 direction,
    glm::vec3 ambient,
    glm::vec3 diffuse,
    glm::vec3 specular);

    void Uniform(ShaderProgram& shaderProgram, std::string unifornName);


private:
    glm::vec3 direction;
    glm::vec3 ambient;
    glm::vec3 diffuse;
    glm::vec3 specular;
};

#endif