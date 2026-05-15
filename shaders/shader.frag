#version 460 core

// Output color variable that maps straight to your screen pixels
out vec4 FragColor;

void main() {
    // Output a solid neon cyan color (Red=0.0, Green=1.0, Blue=1.0, Alpha=1.0)
    FragColor = vec4(0.0, 1.0, 1.0, 1.0);
}