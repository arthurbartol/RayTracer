// renderer/renderer.h

#pragma once

#include <GL/glew.h>
#include <glm/glm.hpp>

class Renderer {
public:
    Renderer();
    ~Renderer();

    void initialize();
    void render();
    void setViewportSize(int width, int height);

private:
    GLuint m_vao;
    GLuint m_vbo;
    GLuint m_shaderProgram;

    void createQuad();
    void createShaders();
};
