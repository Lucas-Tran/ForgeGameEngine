#include <iostream>
#include <glad/glad.h>
#include <GLFW/glfw3.h>

const char *vertexShaderSource =
"#version 330 core\n"
"\n"
"layout (location = 0) in vec3 inPosition;\n"
"\n"
"void main() {\n"
"   gl_Position = vec4(inPosition, 1.0f);\n"
"}";

const char *fragmentShaderSource =
"#version 330 core\n"
"\n"
"out vec4 outColor;\n"
"\n"
"void main() {\n"
"   outColor = vec4(0.7f, 0.5f, 0.1f, 1.0f);\n"
"}";

const float vertices[] = {
    -0.5f, -0.5f, 0.0f,
     0.5f, -0.5f, 0.0f,
     0.0f,  0.5f, 0.0f
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
    GLFWwindow *window = glfwCreateWindow(500, 500, "Hello Triangle", nullptr, nullptr);
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

    
    // Create and compile vertex shader
    const unsigned int vertexShader = glCreateShader(GL_VERTEX_SHADER);
    glShaderSource(vertexShader, 1, &vertexShaderSource, nullptr);
    glCompileShader(vertexShader);

    // Create and compile fragment shader
    const unsigned int fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
    glShaderSource(fragmentShader, 1, &fragmentShaderSource, nullptr);
    glCompileShader(fragmentShader);

    // Create shader program and link shaders
    const unsigned int shaderProgram = glCreateProgram();
    glAttachShader(shaderProgram, vertexShader);
    glAttachShader(shaderProgram, fragmentShader);
    glLinkProgram(shaderProgram);

    // Delete shaders since they are in the shader program and no longer in use
    glDeleteShader(vertexShader);
    glDeleteShader(fragmentShader);


    unsigned int VBO, VAO;

    // Generate vertex array object (VAO)
    glGenVertexArrays(1, &VAO);
    glBindVertexArray(VAO);

    // Generate vertex buffer object (VBO) and uploading the vertex data to it
    glGenBuffers(1, &VBO);
    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

    // Vertex attributes

    // Position
    glEnableVertexAttribArray(0);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void *)(0));

    // Unbind
    glBindVertexArray(0);
    glBindBuffer(GL_ARRAY_BUFFER, 0);


    // Set the clear color
    glClearColor(0.1, 0.2, 0.3, 1.0f);

    // Clear the color buffer
    glClear(GL_COLOR_BUFFER_BIT);

    // Use shader
    glUseProgram(shaderProgram);

    // Draw triangle
    glBindVertexArray(VAO);
    glDrawArrays(GL_TRIANGLES, 0, 3);
    glBindVertexArray(0);

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
    // Clean up shader program
    glDeleteProgram(shaderProgram);

    // Clean up VBO and VAO
    glDeleteBuffers(1, &VBO);
    glDeleteVertexArrays(1, &VAO);

    // Once this loop ended, make sure to destroy this window and terminate GLFW to remove all or it's allocated resources
    glfwDestroyWindow(window);
    glfwTerminate();
    return 0;
}
