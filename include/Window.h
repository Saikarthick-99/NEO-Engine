#pragma once

#include <string>
#include <glad/glad.h>
#include <GLFW/glfw3.h>

class Window {
public:
    Window(int width, int height, const std::string& title);
    ~Window();

    bool shouldClose() const;
    void update();
    void clear(float r, float g, float b, float a);

private:
    GLFWwindow* m_windowHandle;
    int m_width;
    int m_height;
    std::string m_title;

    bool init();
};