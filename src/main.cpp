/*
** EPITECH PROJECT, 2019
** openGl
** File description:
** main.cpp
*/

#include <GL/glew.h>

#include "AppWindow.hpp"
#include "ShaderManager.hpp"

struct Position2d
{
    float x;
    float y;
};

struct Color
{
    float r;
    float g;
    float b;
    float a;
};

struct MyVertex
{
    Position2d pos;
    Color col;
};

int main()
{
    AppWindow window;

    MyVertex vertices[4]{
        {{-0.5f, -0.5f}, {1, 0, 0, 1}},
        {{-0.5f, 0.5f}, {0, 1, 0, 1}},
        {{0.5f, 0.5f}, {0, 0, 1, 1}},
        {{0.5f, -0.5f}, {0, 1, 0, 1}},
    };
    unsigned int indices[]{
        0, 1, 2,
        0, 2, 3
    };

    GLuint vbo;
    glGenBuffers(1, &vbo);

    glBindBuffer(GL_ARRAY_BUFFER, vbo);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

    GLuint vao;
    glGenVertexArrays(1, &vao);
    glBindVertexArray(vao);
    glVertexAttribPointer(0,
                          2,
                          GL_FLOAT,
                          GL_FALSE,
                          sizeof(MyVertex),
                          (void *) offsetof(MyVertex, pos));
    glEnableVertexAttribArray(0);
    glVertexAttribPointer(1,
                          4,
                          GL_FLOAT,
                          GL_FALSE,
                          sizeof(MyVertex),
                          (void *) offsetof(MyVertex, col));
    glEnableVertexAttribArray(1);

    ShaderManager sm;

    sm.addShader(GL_VERTEX_SHADER, "vertex.shader");
    sm.addShader(GL_FRAGMENT_SHADER, "fragment.shader");
    sm.validate();

    while (window.run()) {
        glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, indices);
//                glDrawArrays(GL_TRIANGLES, 0, 3);
    }
}
