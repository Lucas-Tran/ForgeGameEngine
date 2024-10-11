#include <VBO.h>

#include <glad/glad.h>

VBO::VBO(const float *vertices, const unsigned int bufferSize) {
    // Generate vertex buffer object into this object's ID
    glGenBuffers(1, &ID);
    // Bind the buffer to OpenGL and upload the data
    Bind();
    glBufferData(GL_ARRAY_BUFFER, bufferSize, vertices, GL_STATIC_DRAW);
}

VBO::~VBO() {
    // Once this object is deleted, make sure to also delete the buffer stored in OpenGL
    glDeleteBuffers(1, &ID);
}

void VBO::Bind() const {
    glBindBuffer(GL_ARRAY_BUFFER, ID);
}

void VBO::Unbind() {
    glBindBuffer(GL_ARRAY_BUFFER, 0);
}