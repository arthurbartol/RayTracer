#include <GLFW/glfw3.h>

#include <iostream>

int main() {
    std::cout << "Initializing raytracer..." << std::endl;

    if (!glfwInit()) {
        std::cerr << "Failed to initialize GLFW" << std::endl;
        return -1;
    }

    GLFWwindow* window = glfwCreateWindow(640, 480, "raytracer", nullptr, nullptr);
    if (!window) {
        std::cerr << "Failed to create a GLFW window" << std::endl;
        glfwTerminate();
        return -1;
    }

    glfwMakeContextCurrent(window);

    while (!glfwWindowShouldClose(window)) {
        glfwPollEvents();
    }

    glfwDestroyWindow(window);
    glfwTerminate();
    
    return 0;
}
