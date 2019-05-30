/*
** EPITECH PROJECT, 2019
** Project
** File description:
** ShaderManager.hpp
*/

#pragma once

#include <vector>
#include <string>
#include <GL/glew.h>

class ShaderManager
{
public:
    ~ShaderManager();
    void addShader(GLenum type, const std::string &path);
    void validate();

private:
    static const char *kShaderDir;

    bool _validated = false;
    std::vector<GLuint> _shaders;
    GLuint _program;
};

GLuint createShader(const char *vertexShader, char const *fragmentShader);
