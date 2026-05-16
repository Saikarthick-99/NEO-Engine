#version 460 core
out vec4 FragColor;

in vec2 TexCoord;

// Declaring separate texture sample locations
uniform sampler2D texture1;
uniform sampler2D texture2;

void main() {
    // Linearly blend both textures together. 
    // The third parameter (0.2) means: 80% texture1 + 20% texture2
    FragColor = mix(texture(texture1, TexCoord), texture(texture2, TexCoord), 0.2);
}