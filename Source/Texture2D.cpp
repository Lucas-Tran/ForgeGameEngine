#include <Texture2D.h>

#include <glad/glad.h>

#include <stb_image.h>
#include <iostream>

Texture2D::Texture2D(const std::string path, const unsigned int textureSlot, const unsigned int sWrapping, const unsigned int tWrapping, const unsigned int minFiltering, const unsigned int magFiltering): textureSlot(textureSlot) {
    // Create a texture into this ID, set the slot to use, and bind the texture
    glGenTextures(1, &ID);
    glActiveTexture(GL_TEXTURE0 + textureSlot);
    glBindTexture(GL_TEXTURE_2D, ID);

    // We load the image recording the width, height, and channels
    int width, height, channels;
    stbi_set_flip_vertically_on_load(true); // This is because stbi loads the images flipped by default
    unsigned char *data = stbi_load(path.c_str(), &width, &height, &channels, 0);
    if (data) {
        // This means we successfully loaded in the image
        unsigned int format = (channels == 3) ? GL_RGB : GL_RGBA;
        glTexImage2D(GL_TEXTURE_2D, 0, format, width, height, 0, format, GL_UNSIGNED_BYTE, data);
        glGenerateMipmap(GL_TEXTURE_2D);
        stbi_image_free(data);
    } else {
        // This means we failed to load in the image so we set our ID to 0, log and error message and end the function
        ID = 0;
        std::cout << "ERROR::TEXTURE::LOADING::FAILED: " << path << std::endl;
        return;
    }

    // Define how to wrap our textures
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, sWrapping);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, tWrapping);

    // Define how to filter our textures
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, minFiltering);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, magFiltering);
}

Texture2D::~Texture2D() {
    // When this object is deleted, we also need to delete the object stored in OpenGL
    glDeleteTextures(1, &ID);
}

bool Texture2D::Success() const {
    return ID != 0;
}

void Texture2D::Uniform(ShaderProgram &shaderProgram, const std::string uniformName) const {
    shaderProgram.SetUniform(uniformName, textureSlot);
}