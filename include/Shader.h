#pragma once

#include <string>
#include <glad/glad.h>

class Shader {
public:
    // Holds the final compiled GPU program ID identifier
    unsigned int ID;

    // Constructor reads and builds the shader instantly
    Shader(const std::string& vertexPath, const std::string& fragmentPath);
    ~Shader();

    // Tell the GPU to activate this shader program for subsequent draw calls
    void use() const;

private:
    // Helper function to check for compilation/linking compiler errors
    void checkCompileErrors(unsigned int shader, const std::string& type);
};