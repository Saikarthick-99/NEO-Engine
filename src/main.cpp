#include <iostream>

// CRITICAL: Glad must always be included before GLFW!
#include <glad/glad.h>
#include <GLFW/glfw3.h>

int main() {
    std::cout << "============================================" << std::endl;
    std::cout << "        NEO ENGINE INITIALIZATION           " << std::endl;
    std::cout << "============================================" << std::endl;

    // Test if GLFW is linking properly by executing a safe command
    int major, minor, revision;
    glfwGetVersion(&major, &minor, &revision);
    
    std::cout << "[SUCCESS] NEO Base Core Compiled!" << std::endl;
    std::cout << "[INFO] Bound GLFW Version: " << major << "." << minor << "." << revision << std::endl;
    std::cout << "============================================" << std::endl;

    return 0;
}