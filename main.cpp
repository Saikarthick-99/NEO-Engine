#include "Window.h"
#include "Shader.h"
#include <iostream>
#include <glm.hpp>
#include <gtc/matrix_transform.hpp>
#include <gtc/type_ptr.hpp>
#include <../dependencies/stb_image.h>

int main() {
    std::cout << "Starting NEO Engine Pipeline Run..." << std::endl;

    // 1. Create the window FIRST. 
    // The constructor handles glfwMakeContextCurrent and gladLoadGLLoader allocations.
    Window window(1280, 720, "NEO Engine | Graphics Pipeline");

    // 2. ONLY NOW can you call OpenGL hardware functions.
    Shader ourShader("shaders/shader.vert", "shaders/shader.frag");

    // 2D Quad geometry mapping out both Clip Space and UV coordinate bounds
    float vertices[] = {
        // Positions          // UV Coordinates
         0.5f,  0.5f, 0.0f,   1.0f, 1.0f,   // Top Right
         0.5f, -0.5f, 0.0f,   1.0f, 0.0f,   // Bottom Right
        -0.5f, -0.5f, 0.0f,   0.0f, 0.0f,   // Bottom Left
        -0.5f,  0.5f, 0.0f,   0.0f, 1.0f    // Top Left 
    };

    unsigned int indices[] = {
        0, 1, 3, // First Triangle
        1, 2, 3  // Second Triangle
    };

    // FIXED: Explicitly allocate the EBO handle along with the VAO and VBO buffers
    unsigned int VAO, VBO, EBO;
    glGenVertexArrays(1, &VAO);
    glGenBuffers(1, &VBO);
    glGenBuffers(1, &EBO);

    // Bind the Vertex Array Object first to capture state rules
    glBindVertexArray(VAO);

    // Bind and upload vertex array data string mappings
    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

    // Bind and upload index element array vectors
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);

    // Position Attribute Layout Mapping (Location = 0)
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);

    // Texture Coordinate Attribute Layout Mapping (Location = 1)
    glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*)(3 * sizeof(float)));
    glEnableVertexAttribArray(1);

    // Unbind VAO first to seal pipeline state config rules
    glBindVertexArray(0);
    glBindBuffer(GL_ARRAY_BUFFER, 0);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0); // Safe to unbind after VAO is closed

    // --- TEXTURE UNIT 0 SETUP (Base Container) ---
    unsigned int textureID;
    glGenTextures(1, &textureID);
    glBindTexture(GL_TEXTURE_2D, textureID);

    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

    int width, height, nrChannels;
    unsigned char* data = stbi_load("assets/container.png", &width, &height, &nrChannels, 0);

    if (data) {
        GLenum format = (nrChannels == 4) ? GL_RGBA : GL_RGB;
        glTexImage2D(GL_TEXTURE_2D, 0, format, width, height, 0, format, GL_UNSIGNED_BYTE, data);
        glGenerateMipmap(GL_TEXTURE_2D);
        stbi_image_free(data);
    }
    else {
        std::cerr << "[NEO ENGINE] Failed to load engine texture asset: assets/container.png" << std::endl;
    }

    // --- TEXTURE UNIT 1 SETUP (Overlay Logo) ---
    unsigned int textureID2;
    glGenTextures(1, &textureID2);
    glBindTexture(GL_TEXTURE_2D, textureID2);

    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

    // Flips coordinate origin alignment so texture mapping direction faces upright
    stbi_set_flip_vertically_on_load(true);

    int width2, height2, nrChannels2;
    unsigned char* data2 = stbi_load("assets/logo.png", &width2, &height2, &nrChannels2, 0);

    if (data2) {
        GLenum format = (nrChannels2 == 4) ? GL_RGBA : GL_RGB;
        glTexImage2D(GL_TEXTURE_2D, 0, format, width2, height2, 0, format, GL_UNSIGNED_BYTE, data2);
        glGenerateMipmap(GL_TEXTURE_2D);
        stbi_image_free(data2);
    }
    else {
        std::cerr << "[NEO ENGINE] Failed to load engine texture asset: assets/logo.png" << std::endl;
    }

    // Connect GLSL texture uniforms to continuous explicit tracking channels
    ourShader.use();
    glUniform1i(glGetUniformLocation(ourShader.ID, "texture1"), 0); // Links to GL_TEXTURE0
    glUniform1i(glGetUniformLocation(ourShader.ID, "texture2"), 1); // Links to GL_TEXTURE1

    // --- CORE MAIN RUN TIME LOOP ---
    while (!window.shouldClose()) {
        // Wipe graphics surface back-buffer clean
        window.clear(0.1f, 0.14f, 0.18f, 1.0f);

        // Active program shader parameters
        ourShader.use();

        // Map sampling arrays onto hardware streams
        glActiveTexture(GL_TEXTURE0);
        glBindTexture(GL_TEXTURE_2D, textureID);

        glActiveTexture(GL_TEXTURE1);
        glBindTexture(GL_TEXTURE_2D, textureID2);

        // 1. Model Matrix: Position the object in the world and rotate it over time
        glm::mat4 model = glm::mat4(1.0f);
        float timeValue = (float)glfwGetTime();
        model = glm::rotate(model, timeValue * glm::radians(50.0f), glm::vec3(0.5f, 1.0f, 0.0f));

        // 2. View Matrix: Move the world context backward to simulate a camera looking forward
        glm::mat4 view = glm::mat4(1.0f);
        // Note: Moving the scene away from us in the negative Z direction
        view = glm::translate(view, glm::vec3(0.0f, 0.0f, -3.0f));

        // 3. Projection Matrix: Apply 3D field-of-view perspective calculations 
        glm::mat4 projection = glm::mat4(1.0f);
        projection = glm::perspective(glm::radians(45.0f), 1280.0f / 720.0f, 0.1f, 100.0f);

        // Retrieve uniform allocation slots from our compiled shader
        unsigned int modelLoc = glGetUniformLocation(ourShader.ID, "model");
        unsigned int viewLoc = glGetUniformLocation(ourShader.ID, "view");
        unsigned int projLoc = glGetUniformLocation(ourShader.ID, "projection");

        // Upload the three 4x4 matrix data arrays straight to the GPU hardware
        glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
        glUniformMatrix4fv(viewLoc, 1, GL_FALSE, glm::value_ptr(view));
        glUniformMatrix4fv(projLoc, 1, GL_FALSE, glm::value_ptr(projection)); 

        glBindVertexArray(VAO);

        // FIXED: Swapped out glDrawArrays for indexed drawing execution to render the full 6-point quad
        glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);

        // Alternate back-buffer graphics arrays safely to display new frames
        window.update();
    }

    // Clean hardware asset mappings out of VRAM memory boundaries before closing
    glDeleteVertexArrays(1, &VAO);
    glDeleteBuffers(1, &VBO);
    glDeleteBuffers(1, &EBO); // Clean up the newly generated EBO resource allocation

    std::cout << "Engine shutting down safely..." << std::endl;
    return 0;
}