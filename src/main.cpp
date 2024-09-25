// src/main.cpp

#include "window.h"

#include <iostream>

int main() {
    try {
        Window window(800, 600, "raytracer");

        while (!window.shouldClose()) {
            // Future rendering code

            window.swapBuffers();
            window.pollEvents();
        }
    } catch (const std::exception& e) {
        std::cerr << "Error: " << e.what() << std::endl;
        return -1;
    }

    return 0;
}
