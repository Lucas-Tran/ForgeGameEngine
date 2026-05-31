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

// Camera
#include <Camera.h>

// Engine
#include <ForgeEngine.h>

// Lights
#include <DirectionalLight.h>
#include <PointLight.h>
#include <SpotLight.h>

// Material
#include <Material.h>

float vertices[] = {
    //  POSITION                // TEXTURE COORDS   // NORMALS (Facing direction)
    // Back Face (Facing straight down the negative Z-axis)
     0.5f, -0.5f, -0.5f,         0.0f, 0.0f,         0.0f,  0.0f, -1.0f,
    -0.5f, -0.5f, -0.5f,         1.0f, 0.0f,         0.0f,  0.0f, -1.0f,
    -0.5f,  0.5f, -0.5f,         1.0f, 1.0f,         0.0f,  0.0f, -1.0f,
     0.5f,  0.5f, -0.5f,         0.0f, 1.0f,         0.0f,  0.0f, -1.0f,

    // Left Face (Facing straight down the negative X-axis)
    -0.5f, -0.5f, -0.5f,         0.0f, 0.0f,        -1.0f,  0.0f,  0.0f,
    -0.5f, -0.5f,  0.5f,         1.0f, 0.0f,        -1.0f,  0.0f,  0.0f,
    -0.5f,  0.5f,  0.5f,         1.0f, 1.0f,        -1.0f,  0.0f,  0.0f,
    -0.5f,  0.5f, -0.5f,         0.0f, 1.0f,        -1.0f,  0.0f,  0.0f,

    // Front Face (Facing straight down the positive Z-axis)
    -0.5f, -0.5f,  0.5f,         0.0f, 0.0f,         0.0f,  0.0f,  1.0f,
     0.5f, -0.5f,  0.5f,         1.0f, 0.0f,         0.0f,  0.0f,  1.0f,
     0.5f,  0.5f,  0.5f,         1.0f, 1.0f,         0.0f,  0.0f,  1.0f,
    -0.5f,  0.5f,  0.5f,         0.0f, 1.0f,         0.0f,  0.0f,  1.0f,

    // Right Face (Facing straight down the positive X-axis)
     0.5f, -0.5f,  0.5f,         0.0f, 0.0f,         1.0f,  0.0f,  0.0f,
     0.5f, -0.5f, -0.5f,         1.0f, 0.0f,         1.0f,  0.0f,  0.0f,
     0.5f,  0.5f, -0.5f,         1.0f, 1.0f,         1.0f,  0.0f,  0.0f,
     0.5f,  0.5f,  0.5f,         0.0f, 1.0f,         1.0f,  0.0f,  0.0f,

    // Top Face (Facing straight up the positive Y-axis)
    -0.5f,  0.5f,  0.5f,         0.0f, 0.0f,         0.0f,  1.0f,  0.0f,
     0.5f,  0.5f,  0.5f,         1.0f, 0.0f,         0.0f,  1.0f,  0.0f,
     0.5f,  0.5f, -0.5f,         1.0f, 1.0f,         0.0f,  1.0f,  0.0f,
    -0.5f,  0.5f, -0.5f,         0.0f, 1.0f,         0.0f,  1.0f,  0.0f,

    // Bottom Face (Facing straight down the negative Y-axis)
    -0.5f, -0.5f, -0.5f,         0.0f, 0.0f,         0.0f, -1.0f,  0.0f,
     0.5f, -0.5f, -0.5f,         1.0f, 0.0f,         0.0f, -1.0f,  0.0f,
     0.5f, -0.5f,  0.5f,         1.0f, 1.0f,         0.0f, -1.0f,  0.0f,
    -0.5f, -0.5f,  0.5f,         0.0f, 1.0f,         0.0f, -1.0f,  0.0f
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
    GLFWwindow *window = glfwCreateWindow(500, 500, "Hello Camera", nullptr, nullptr);
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

    glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);

    ShaderProgram shaderProgram("Shaders/default.VS", "Shaders/default.FS");


    // The importance of the order of creation and unbinding is because the VAO keeps tracks of all bindings and unbindings.

    // Create VAO, VBO, and EBO
    VAO VAO;
    VBO VBO(vertices, sizeof(vertices));

    // Vertex attributes
    // And it is important to set the vertex attributes after the VBO creation is because the VAO needs to know which buffer this format is for
    VAO::SetVertexAttribute(0, 3, 8, 0); // Position
    VAO::SetVertexAttribute(1, 2, 8, 3); // Texture coordinates
    VAO::SetVertexAttribute(2, 3, 8, 5); // Normal coordinates

    EBO EBO(elements, sizeof(elements));

    // Unbind them
    // The order matters again because if we unbind the buffers before the VAO, the VAO will not know we are using the buffers.
    VAO::Unbind();
    VBO::Unbind();
    EBO::Unbind();

    // Activate shader
    shaderProgram.Activate();

    const float NEAR = 0.1f, FAR = 1000.0f;
    int width, height;
    glfwGetWindowSize(window, &width, &height);
    Camera camera(glm::vec3(0.0f, 0.0f, 3.0f), 0, 0, 60, width, height, NEAR, FAR);
    shaderProgram.SetUniform("projection", camera.GetProjectionMatrix()); // Uniform Projection matrix

    Texture2D diffuseTexture("Textures/container2.png", 0, GL_REPEAT, GL_REPEAT, GL_LINEAR_MIPMAP_LINEAR, GL_LINEAR);
    Texture2D specularTexture("Textures/container2_specular.png", 1, GL_REPEAT, GL_REPEAT, GL_LINEAR_MIPMAP_LINEAR, GL_LINEAR);
    Texture2D white1x1("Textures/white1x1.png", 2, GL_REPEAT, GL_REPEAT, GL_LINEAR_MIPMAP_LINEAR, GL_LINEAR);

    Material boxMaterial {diffuseTexture, specularTexture, 32.0f};
    Material lightMaterial {white1x1, white1x1, 32.0f};

    DirectionalLight directionalLight(
        glm::vec3(0.0f, -1.0f, -1.0f),
        glm::vec3(0.5f, 0.5f, 0.5f),
        glm::vec3(1.0f, 1.0f, 1.0f),
        glm::vec3(1.0f, 1.0f, 1.0f)
    );
    directionalLight.Uniform(shaderProgram, "dirLights[0]");

    PointLight pointLight(
        glm::vec3(0.0f),
        1.0f,
        0.09f,
        0.032f,
        glm::vec3(1.0f, 1.0f, 1.0f),
        glm::vec3(1.0f, 1.0f, 1.0f),
        glm::vec3(1.0f, 1.0f, 1.0f)
    );
    pointLight.Uniform(shaderProgram, "pointLights[0]");


    SpotLight spotlight(
        glm::vec3(0.0f),
        glm::vec3(0.0f),
        12.5f,
        17.5f,
        1.0f,
        0.09f,
        0.032f,
        glm::vec3(0.0f, 0.0f, 0.0f),
        glm::vec3(1.0f, 1.0f, 1.0f),
        glm::vec3(1.0f, 1.0f, 1.0f)
    );

    glm::vec3 lightPosition(0.0f, 4.0f, 0.0f);

    // Game Loop
    while (true) {
        // Process the events
        glfwPollEvents();
        
        // If the window needs to close, break out of this loop
        if (glfwWindowShouldClose(window) || (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)) {
            break;
        }

        UpdateProgramState(window);
        

        camera.Update();
        shaderProgram.SetUniform("viewPos", camera.GetPos());
        shaderProgram.SetUniform("view", camera.GetViewMatrix());

        // Flashlight example: Attach to camera vectors
        spotlight.SetPosition(camera.GetPos());
        spotlight.SetForward(camera.GetForwardVector());
        spotlight.Uniform(shaderProgram, "spotLights[0]");
        
        float theta = glfwGetTime();
        lightPosition.x = 4.0f * cos(theta);
        lightPosition.z = 4.0f * sin(theta);
        pointLight.SetPosition(lightPosition);
        pointLight.Uniform(shaderProgram, "pointLights[0]");

        // Set the clear color
        glClearColor(0.1, 0.2, 0.3, 1.0f);

        // Clear the color buffer
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
        
        // The box
        glm::mat4 model(1.0f);
        model = glm::scale(model, glm::vec3(4.0f));

        shaderProgram.SetUniform("model", model);
        boxMaterial.Uniform(shaderProgram, "material");

        VAO.Bind();
        glDrawElements(GL_TRIANGLES, 36, GL_UNSIGNED_INT, (void *)(0));
        VAO::Unbind();
        
        // The light
        model = glm::mat4(1.0f);
        model = glm::translate(model, lightPosition);

        shaderProgram.SetUniform("model", model);
        lightMaterial.Uniform(shaderProgram, "material");

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
