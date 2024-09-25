// core/window.h

#pragma once

#include <GLFW/glfw3.h>

#include <string>

class Window {
public:
    int width;
    int height;

    Window(int width, int height, const std::string& title);
    ~Window();

    bool shouldClose() const;
    void swapBuffers();
    void pollEvents();

private:
    GLFWwindow* m_window;
};
