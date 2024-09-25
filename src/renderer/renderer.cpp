// renderer/renderer.cpp

#include "renderer.h"

#include <iostream>
#include <vector>
#include <stdexcept>

const char* vertexShaderSource = R"(
    #version 400 core

    layout (location = 0) in vec3 pos;
    layout (location = 1) in vec2 texCoord;

    out vec2 TexCoord;

    void main() {
        gl_Position = vec4(pos.x, pos.y, pos.z, 1.0);
        TexCoord = texCoord;
    }
)";

const char* fragmentShaderSource = R"(
    #version 400 core

    in vec2 TexCoord;
    out vec4 FragColor;

    void main() {
        FragColor = vec4(TexCoord.x, TexCoord.y, 0.0, 1.0);
    }
)";

Renderer::Renderer() : m_vao(0), m_vbo(0), m_shaderProgram(0) {}

Renderer::~Renderer() {
    glDeleteVertexArrays(1, &m_vao);
    glDeleteBuffers(1, &m_vbo);
    glDeleteProgram(m_shaderProgram);
}

void Renderer::initialize() {
    glewExperimental = GL_TRUE;
    if (glewInit() != GLEW_OK) {
        throw std::runtime_error("Failed to initialize GLEW");
    }
    createQuad();
    createShaders();
}

void Renderer::render() {
    glClear(GL_COLOR_BUFFER_BIT);
    glClearColor(0.5f, 0.0f, 0.5f, 1.0f);
    glUseProgram(m_shaderProgram);
    glBindVertexArray(m_vao);
    glDrawArrays(GL_TRIANGLES, 0, 6);
}

void Renderer::setViewportSize(int width, int height) {
    glViewport(0, 0, width, height);
}

void Renderer::createQuad() {
    float vertices[] = {
        // positions        // texture coords
        -1.0f,  1.0f, 0.0f, 0.0f, 1.0f,
        -1.0f, -1.0f, 0.0f, 0.0f, 0.0f,
         1.0f, -1.0f, 0.0f, 1.0f, 0.0f,
        -1.0f,  1.0f, 0.0f, 0.0f, 1.0f,
         1.0f, -1.0f, 0.0f, 1.0f, 0.0f,
         1.0f,  1.0f, 0.0f, 1.0f, 1.0f
    };

    glGenVertexArrays(1, &m_vao);
    glGenBuffers(1, &m_vbo);

    glBindVertexArray(m_vao);

    glBindBuffer(GL_ARRAY_BUFFER, m_vbo);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);

    glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*)(3 * sizeof(float)));
    glEnableVertexAttribArray(1);
}

void Renderer::createShaders() {
    GLuint vertexShader = glCreateShader(GL_VERTEX_SHADER);
    glShaderSource(vertexShader, 1, &vertexShaderSource, nullptr);
    glCompileShader(vertexShader);

    GLuint fragmentShader = glCreateShader(GL_VERTEX_SHADER);
    glShaderSource(fragmentShader, 1, &fragmentShaderSource, nullptr);
    glCompileShader(fragmentShader);

    m_shaderProgram = glCreateProgram();
    glAttachShader(m_shaderProgram, vertexShader);
    glAttachShader(m_shaderProgram, fragmentShader);
    glLinkProgram(m_shaderProgram);

    glDeleteShader(vertexShader);
    glDeleteShader(fragmentShader);
}
