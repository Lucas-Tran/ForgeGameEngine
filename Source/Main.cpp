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

// For easy matrix transformations
#include <glm/gtc/matrix_transform.hpp>

const float vertices[] = {
    //  POSITION                // TEXTURE COORDINATES
     0.5f, -0.5f, -0.5f,         0.0f, 0.0f,
    -0.5f, -0.5f, -0.5f,         1.0f, 0.0f,
    -0.5f,  0.5f, -0.5f,         1.0f, 1.0f,
     0.5f,  0.5f, -0.5f,         0.0f, 1.0f,


    -0.5f, -0.5f, -0.5f,         0.0f, 0.0f,
    -0.5f, -0.5f,  0.5f,         1.0f, 0.0f,
    -0.5f,  0.5f,  0.5f,         1.0f, 1.0f,
    -0.5f,  0.5f, -0.5f,         0.0f, 1.0f,


    -0.5f, -0.5f,  0.5f,         0.0f, 0.0f,
     0.5f, -0.5f,  0.5f,         1.0f, 0.0f,
     0.5f,  0.5f,  0.5f,         1.0f, 1.0f,
    -0.5f,  0.5f,  0.5f,         0.0f, 1.0f,


     0.5f, -0.5f,  0.5f,         0.0f, 0.0f,
     0.5f, -0.5f, -0.5f,         1.0f, 0.0f,
     0.5f,  0.5f, -0.5f,         1.0f, 1.0f,
     0.5f,  0.5f,  0.5f,         0.0f, 1.0f,


    -0.5f,  0.5f,  0.5f,         0.0f, 0.0f,
     0.5f,  0.5f,  0.5f,         1.0f, 0.0f,
     0.5f,  0.5f, -0.5f,         1.0f, 1.0f,
    -0.5f,  0.5f, -0.5f,         0.0f, 1.0f,


    -0.5f, -0.5f, -0.5f,         0.0f, 0.0f,
     0.5f, -0.5f, -0.5f,         1.0f, 0.0f,
     0.5f, -0.5f,  0.5f,         1.0f, 1.0f,
    -0.5f, -0.5f,  0.5f,         0.0f, 1.0f,
};

const unsigned int elements[] = {
    0, 1, 2,
    0, 2, 3,

    4, 5, 6,
    4, 6, 7,

    8, 9, 10,
    8, 10, 11,

    12, 13, 14,
    12, 14, 15,

    16, 17, 18,
    16, 18, 19,

    20, 21, 22,
    20, 22, 23
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
    GLFWwindow *window = glfwCreateWindow(500, 500, "Hello Cube", nullptr, nullptr);
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

    glEnable(GL_DEPTH_TEST); // Enable depth testing
    glEnable(GL_CULL_FACE); // Enable face culling

    ShaderProgram shaderProgram("Shaders/default.VS", "Shaders/default.FS");


    // The importance of the order of creation and unbinding is because the VAO keeps tracks of all bindings and unbindings.

    // Create VAO, VBO, and EBO
    VAO VAO;
    VBO VBO(vertices, sizeof(vertices));

    // Vertex attributes
    // And it is important to set the vertex attributes after the VBO creation is because the VAO needs to know which buffer this format is for
    VAO::SetVertexAttribute(0, 3, 5, 0); // Position
    VAO::SetVertexAttribute(1, 2, 5, 3); // Texture coordinates

    EBO EBO(elements, sizeof(elements));

    // Unbind them
    // The order matters again because if we unbind the buffers before the VAO, the VAO will not know we are using the buffers.
    VAO::Unbind();
    VBO::Unbind();
    EBO::Unbind();

    Texture2D texture("Textures/GrassBlock.png", 0, GL_REPEAT, GL_REPEAT, GL_LINEAR_MIPMAP_LINEAR, GL_NEAREST);

    const float NEAR = 0.1f, FAR = 1000.0f;
    int width, height;
    glfwGetWindowSize(window, &width, &height);
    glm::mat4 projection = glm::perspective(glm::radians(60.0f), (float)width/height, NEAR, FAR);

    // Activate shader
    shaderProgram.Activate();

    texture.Uniform(shaderProgram, "texture_0"); // Uniform Texture
    shaderProgram.SetUniform("projection", projection); // Uniform Projection matrix

    // Game Loop
    while (true) {
        // Process the events
        glfwPollEvents();
        
        // If the window needs to close, break out of this loop
        if (glfwWindowShouldClose(window)) {
            break;
        }
        
        glm::mat4 model(1.0f);
        model = glm::translate(model, glm::vec3(0.0f, 0.0f, -3.0f));
        model = glm::rotate(model, (float)glfwGetTime(), glm::vec3(1.0f, 1.0f, 0.0f));

        shaderProgram.SetUniform("model", model);

        // Set the clear color
        glClearColor(0.1, 0.2, 0.3, 1.0f);

        // Clear the color buffer
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        // Draw triangle
        VAO.Bind();
        glDrawElements(GL_TRIANGLES, 36, GL_UNSIGNED_INT, (void *)(0));
        VAO::Unbind();
        
        // Swap the buffers to display our new back buffer
        glfwSwapBuffers(window);
    }

    // Once this loop ended, make sure to destroy this window and terminate GLFW to remove all or it's allocated resources
    glfwDestroyWindow(window);
    glfwTerminate();
    return 0;
}
