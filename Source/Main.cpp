#include <iostream>
#include <glad/glad.h>
#include <GLFW/glfw3.h>

// Shader program
#include <ShaderProgram.h>

// VBO, EBO & VAO
#include <VBO.h>
#include <EBO.h>
#include <VAO.h>

// Texture 2D
#include <Texture2D.h>

const float vertices[] = {
    //  POSITION                // TEXTURE COORDINATES
    -0.5f, -0.5f, 0.0f,         0.0f, 0.0f,
     0.5f, -0.5f, 0.0f,         1.0f, 0.0f,
     0.5f,  0.5f, 0.0f,         1.0f, 1.0f,
    -0.5f,  0.5f, 0.0f,         0.0f, 1.0f
};

const unsigned int elements[] = {
    0, 1, 2,
    0, 2, 3
};

int main() {
    // Attempt to initialize GLFW
    if (!glfwInit()) {
        std::cerr << "Failed to initialize GLFW!" << std::endl;
        return 1;
    }

    // Give the window hints
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
#ifdef __APPLE__
    glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, true);
#endif

    // Attempt to create window
    GLFWwindow *window = glfwCreateWindow(500, 500, "Hello Quad", nullptr, nullptr);
    if (window == nullptr) {
        std::cerr << "Failed to create window!" << std::endl;
        return 1;
    }

    // Set the current context of the thread to be this window
    glfwMakeContextCurrent(window);
    
    // Attempt to initialize GLAD
    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)) {
        std::cerr << "Failed to initialize GLAD" << std::endl;
        return 1;
    }

    ShaderProgram shaderProgram("Shaders/default.VS", "Shaders/default.FS");


    // The importance of the order of creation and unbinding is because the VAO keeps tracks of all bindings and unbindings.

    // Create VAO, VBO, and EBO
    VAO VAO;
    VBO VBO(vertices, sizeof(vertices));

    // Vertex attributes
    // And it is important to set the vertex attributes after the VBO creation is because the VAO needs to know which buffer this format is for
    VAO::SetVertexAttribute(0, 3, 5, 0); // Position
    VAO::SetVertexAttribute(1, 2, 5, 3); // Position

    EBO EBO(elements, sizeof(elements));

    // Unbind them
    // The order matters again because if we unbind the buffers before the VAO, the VAO will not know we are using the buffers.
    VAO::Unbind();
    VBO::Unbind();
    EBO::Unbind();

    Texture2D texture("Textures/GrassBlock.png", 0, GL_REPEAT, GL_REPEAT, GL_NEAREST_MIPMAP_LINEAR, GL_NEAREST);



    // Set the clear color
    glClearColor(0.1, 0.2, 0.3, 1.0f);

    // Clear the color buffer
    glClear(GL_COLOR_BUFFER_BIT);

    // Activate shader
    shaderProgram.Activate();
    texture.Uniform(shaderProgram, "texture_0");

    // Draw triangle
    VAO.Bind();
    glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, (void *)(0));
    VAO::Unbind();

    // Swap the buffers to display our new back buffer
    glfwSwapBuffers(window);

    // Game Loop
    while (true) {
        // Process the events
        glfwPollEvents();
        
        // If the window needs to close, break out of this loop
        if (glfwWindowShouldClose(window)) {
            break;
        }
    }

    // Once this loop ended, make sure to destroy this window and terminate GLFW to remove all or it's allocated resources
    glfwDestroyWindow(window);
    glfwTerminate();
    return 0;
}
