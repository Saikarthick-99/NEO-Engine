#version 460 core
layout (location = 0) in vec3 aPos;

uniform mat4 transform; // Our rotation matrix passed from C++

void main() {
    // Multiply the matrix by the position vector
    // CRITICAL: Matrix multiplication order matters in GLSL (Matrix * Vector)
    gl_Position = transform * vec4(aPos, 1.0);
}