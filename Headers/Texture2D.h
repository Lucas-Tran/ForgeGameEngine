#ifndef TEXTURE2D_H_INCLUDED
#define TEXTURE2D_H_INCLUDED

#include <string>
#include <ShaderProgram.h>

class Texture2D {
public:
    Texture2D(const std::string path, const unsigned int textureSlot, const unsigned int tWrapping, const unsigned int sWrapping, const unsigned int minFiltering, const unsigned int magFiltering);

    ~Texture2D();

    void Uniform(ShaderProgram &shaderProgram, const std::string uniformName);

    bool Success();
private:
    unsigned int ID;
    const unsigned int textureSlot;
};

#endif