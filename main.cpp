#include "Window.h"
#include "Shader.h"
#include <iostream>
#include <glm.hpp>
#include <gtc/matrix_transform.hpp>
#include <gtc/type_ptr.hpp>

int main() {
    std::cout << "Starting NEO Engine Pipeline Run..." << std::endl;

    // 1. Create the window FIRST. 
    // The constructor calls glfwMakeContextCurrent and gladLoadGLLoader.
    Window window(1280, 720, "NEO Engine | Graphics Pipeline");

    // 2. ONLY NOW can you call OpenGL functions.
    Shader ourShader("shaders/shader.vert", "shaders/shader.frag");

    float vertices[] = {
        -0.5f, -0.5f, 0.0f,
         0.5f, -0.5f, 0.0f,
         0.0f,  0.5f, 0.0f
    };

    unsigned int VAO, VBO;
    glGenVertexArrays(1, &VAO); // This will no longer be NULL
    glGenBuffers(1, &VBO);

    // 1. Bind the Vertex Array Object (VAO) to capture layout state configuration settings
    glBindVertexArray(VAO);

    // 2. Bind the Vertex Buffer Object (VBO) and push our local float array to GPU VRAM
    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

    // 3. Define how the GPU should parse our vertex float data array strings (Layout Location 0)
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);

    // Unbind buffers safely to preserve states
    glBindBuffer(GL_ARRAY_BUFFER, 0);
    glBindVertexArray(0);

    // --- CORE MAIN RUN TIME LOOP ---
    while (!window.shouldClose()) {
        // Clear background canvas
        window.clear(0.1f, 0.14f, 0.18f, 1.0f);

        // Activate the compiled shader program pipeline
        ourShader.use();

        // 1. Create an Identity matrix (mathematical equivalent of the number 1)
        glm::mat4 trans = glm::mat4(1.0f);

        // 2. Rotate it over time
        // glfwGetTime() returns a steadily increasing float for smooth motion
        // We rotate around the Z-axis (0, 0, 1) to spin it on a 2D plane
        float timeValue = (float)glfwGetTime();
        trans = glm::rotate(trans, timeValue, glm::vec3(0.0f, 0.0f, 1.0f));

        // 3. Retrieve the uniform location from our compiled shader
        unsigned int transformLoc = glGetUniformLocation(ourShader.ID, "transform");

        // 4. Send the 4x4 matrix data directly to the GPU
        glUniformMatrix4fv(transformLoc, 1, GL_FALSE, glm::value_ptr(trans));

        // Bind our geometric layout and draw
        glBindVertexArray(VAO);
        glDrawArrays(GL_TRIANGLES, 0, 3);

        // Update display window surfaces
        window.update();
    }

    // Clean hardware buffers out of VRAM memory before shutdown
    glDeleteVertexArrays(1, &VAO);
    glDeleteBuffers(1, &VBO);

    std::cout << "Engine shutting down safely..." << std::endl;
    return 0;
}