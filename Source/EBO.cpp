#include <EBO.h>

#include <glad/glad.h>

EBO::EBO(const unsigned int *elements, const unsigned int bufferSize) {
    // Generate element buffer object into this object's ID
    glGenBuffers(1, &ID);
    // Bind the buffer to OpenGL and upload the data
    Bind();
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, bufferSize, elements, GL_STATIC_DRAW);
}

EBO::~EBO() {
    // Once this object is deleted, make sure to also delete the buffer stored in OpenGL
    glDeleteBuffers(1, &ID);
}

void EBO::Bind() const {
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ID);
}

void EBO::Unbind() {
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
}