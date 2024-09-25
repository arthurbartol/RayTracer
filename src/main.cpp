// src/main.cpp

#include "renderer/renderer.h"
#include "core/window.h"

#include <iostream>

int main() {
    try {
        Window window(800, 600, "raytracer");
        Renderer renderer;

        renderer.initialize();
        renderer.setViewportSize(window.width, window.height);

        while (!window.shouldClose()) {
            renderer.render();

            window.swapBuffers();
            window.pollEvents();
        }
    } catch (const std::exception& e) {
        std::cerr << "Error: " << e.what() << std::endl;
        return -1;
    }

    return 0;
}
