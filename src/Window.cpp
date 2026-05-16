#include "Window.h"
#include "../dependencies/stb_image.h"
#include <iostream>


Window::Window(int width, int height, const std::string& title)
    : m_width(width), m_height(height), m_title(title), m_windowHandle(nullptr)
{
    if (!init()) {
        std::cerr << "[ERROR] Failed to initialize Window system!" << std::endl;
    }
}

Window::~Window() {
    if (m_windowHandle) {
        glfwDestroyWindow(m_windowHandle);
    }
    glfwTerminate();
    std::cout << "[Window] System terminated cleanly." << std::endl;
}

bool Window::init() {
    if (!glfwInit()) {
        std::cerr << "[ERROR] Could not initialize GLFW!" << std::endl;
        return false;
    }

    // Force OpenGL 4.6 Core Profile (Turns off slow legacy 90s fixed pipelines)
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 6);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

    m_windowHandle = glfwCreateWindow(m_width, m_height, m_title.c_str(), nullptr, nullptr);
    if (!m_windowHandle) {
        std::cerr << "[ERROR] Failed to create GLFW window!" << std::endl;
        glfwTerminate();
        return false;
    }

    // --- WINDOW ICON SETUP ---
    int width, height, channels;
    // Force 4 channels (RGBA) so GLFW handles the transparency channel natively
    unsigned char* pixels = stbi_load("assets/logo.png", &width, &height, &channels, 4);

    if (pixels) {
        GLFWimage icon[1];
        icon[0].width = width;
        icon[0].height = height;
        icon[0].pixels = pixels;

        // Set the title bar icon context
        glfwSetWindowIcon(m_windowHandle, 1, icon);

        // Free the CPU RAM allocation since pixels are handed to GLFW/GPU
        stbi_image_free(pixels);
    }
    else {
        std::clog << "[NEO ENGINE] Note: Runtime window icon asset not found at assets/icons/logo.png\n";
    }

    glfwMakeContextCurrent(m_windowHandle);

    // Initialize GLAD to parse and fetch your vendor's specific GPU driver functions
    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)) {
        std::cerr << "Failed to initialize GLAD" << std::endl;
        return false;
    }

    
    glEnable(GL_DEBUG_OUTPUT);
    glDebugMessageCallback([](GLenum /*source*/, GLenum type, GLuint /*id*/, GLenum severity, GLsizei /*length*/, const GLchar* message, const void* /*userParam*/) {
        std::cerr << "GL CALLBACK: " << (type == GL_DEBUG_TYPE_ERROR ? "** GL ERROR **" : "")
            << " type = " << type << ", severity = " << severity
            << ", message = " << message << std::endl;
        }, nullptr);

    glViewport(0, 0, m_width, m_height);

    std::cout << "[Window] OpenGL Context created successfully!" << std::endl;
    std::cout << "[Graphics Driver] Vendor:   " << glGetString(GL_VENDOR) << std::endl;
    std::cout << "[Graphics Driver] Renderer: " << glGetString(GL_RENDERER) << std::endl;
    std::cout << "[Graphics Driver] Version:  " << glGetString(GL_VERSION) << std::endl;

    return true;
}

bool Window::shouldClose() const {
    return glfwWindowShouldClose(m_windowHandle);
}

void Window::clear(float r, float g, float b, float a) {
    // State-setting: Choose the canvas wipe color
    glClearColor(r, g, b, a);
    // State-execution: Wipe the color buffer
    glClear(GL_COLOR_BUFFER_BIT);
}

void Window::update() {
    // Swap the frame buffer we are drawing on with the buffer currently visible on screen
    glfwSwapBuffers(m_windowHandle);

    // Check for keyboard, mouse clicks, or window close commands
    glfwPollEvents();

    // Check if user taps ESC key
    if (glfwGetKey(m_windowHandle, GLFW_KEY_ESCAPE) == GLFW_PRESS) {
        glfwSetWindowShouldClose(m_windowHandle, true);
    }
}