#include <VAO.h>

#include <glad/glad.h>

VAO::VAO() {
    // Create the vertex array object (VAO) and bind it
    glGenVertexArrays(1, &ID);
    Bind();
}

VAO::~VAO() {
    // When this object is deleted, we also want to delete the object stored in OpenGL
    glDeleteProgram(ID);
}

void VAO::Bind() const {
    glBindVertexArray(ID);
}

void VAO::Unbind() {
    glBindVertexArray(0);
}

void VAO::SetVertexAttribute(const unsigned int location, const unsigned int attribSize, const unsigned int stride, const unsigned int depth) {
    // We enable the slot we want to use
    glEnableVertexAttribArray(location);
    // Now we tell OpenGL how to transfer data from the buffer to the slot in the shader program
    glVertexAttribPointer(location, attribSize, GL_FLOAT, GL_FALSE, stride * sizeof(float), (void *)(depth * sizeof(float)));
}