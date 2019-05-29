/*
** EPITECH PROJECT, 2019
** openGl
** File description:
** main.cpp
*/

#include <GL/glew.h>
#include <cstdio>
#include <iostream>
#include <cassert>

#include "AppWindow.hpp"

struct MyVertex
{
    float pos_x;
    float pos_y;
};

static GLuint CompileShader(GLenum type, const char *src)
{
    auto shader = glCreateShader(type);

    glShaderSource(shader, 1, &src, nullptr);
    glCompileShader(shader);

    int status;
    glGetShaderiv(shader, GL_COMPILE_STATUS, &status);
    if (status == GL_FALSE) {
        char infoLog[512];
        glGetShaderInfoLog(shader, 512, nullptr, infoLog);
        std::cerr << "Shader compilation : " << infoLog << std::endl;
        glDeleteShader(shader);
        return 0;
    }

    return shader;
}

static GLuint CreateShader(const char *vertexShader,
                           const char *fragmentShader)
{
    auto program = glCreateProgram();

    auto vs = CompileShader(GL_VERTEX_SHADER, vertexShader);
    auto fs = CompileShader(GL_FRAGMENT_SHADER, fragmentShader);

    assert(vs && fs);

    glAttachShader(program, vs);
    glAttachShader(program, fs);
    glLinkProgram(program);

    int status;
    glGetProgramiv(program, GL_LINK_STATUS, &status);
    if (status == GL_FALSE) {
        char infoLog[512];
        glGetProgramInfoLog(program, 512, nullptr, infoLog);
        std::cerr << "Shader compilation : " << infoLog << std::endl;
    }

    glValidateProgram(program);

    glDeleteShader(vs);
    glDeleteShader(fs);

    return program;
}

int main()
{
    AppWindow window;

    MyVertex vertices[]{
        {-0.5f, -0.5f},
        { 0.5f, -0.5f},
        { 0.5f,  0.5f},
        {-0.5f,  0.5f}
    };
    unsigned int indices[] {
        0, 1, 2,
        2, 3, 0
    };

    GLuint vbo, vao;
    glGenBuffers(1, &vbo);
    glGenVertexArrays(1, &vao);


    glBindBuffer(GL_ARRAY_BUFFER, vbo);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

    glBindVertexArray(vao);
    glEnableVertexAttribArray(0);
    glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, sizeof(MyVertex), 0);


    const char *vertexShaderSource = R"(
#version 330 core

layout(location = 0) in vec2 pos;

void main()
{
    gl_Position = vec4(pos.x, pos.y, 0.0f, 1.0f);
}
)";
    const char *fragmentShaderSource = R"(
#version 330 core

out vec4 color;

void main()
{
    color = vec4(1.0f, 0.0f, 0.0f, 1.0f);
}
)";

    auto program = CreateShader(vertexShaderSource, fragmentShaderSource);
    glUseProgram(program);

//    glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);

    while (window.run()) {

        glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, indices);

    }

    glDeleteProgram(program);
}
