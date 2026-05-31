#ifndef POINT_LIGHT_H_INCLUDED
#define POINT_LIGHT_H_INCLUDED

#include <glm/glm.hpp>
#include <ShaderProgram.h>
#include <string>

class PointLight {
public:
    PointLight(
        glm::vec3 position,

        float constant,
        float linear,
        float quadratic,

        glm::vec3 ambient,
        glm::vec3 diffuse,
        glm::vec3 specular
    );

    void Uniform(ShaderProgram& shaderProgram, std::string uniformString);

    void SetPosition(glm::vec3 position);
private:
    glm::vec3 position;

    float constant;
    float linear;
    float quadratic;

    glm::vec3 ambient;
    glm::vec3 diffuse;
    glm::vec3 specular;
};

#endif