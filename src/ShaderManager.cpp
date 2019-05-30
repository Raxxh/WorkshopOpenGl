/*
** EPITECH PROJECT, 2019
** Project
** File description:
** ShaderManager.cpp
*/

#include <fstream>
#include <iostream>
#include "ShaderManager.hpp"

const char *ShaderManager::kShaderDir = "../Shaders/";

ShaderManager::~ShaderManager()
{
    if (_validated)
        glDeleteProgram(_program);
    for (const auto &s : _shaders)
        glDeleteShader(s);
}

void ShaderManager::addShader(GLenum type, const std::string &path)
{
    if (_validated)
        throw std::logic_error("Program already validated");

    std::ifstream file(kShaderDir + path);
    if (!file.is_open()) {
        std::cerr << "Could not open " << kShaderDir + path << ", skipping" << std::endl;
        return;
    }
    std::string content((std::istreambuf_iterator<char>(file)),
                        std::istreambuf_iterator<char>());
    const char *cstr_content = content.c_str();

    auto shader = glCreateShader(type);

    glShaderSource(shader, 1, &cstr_content, nullptr);
    glCompileShader(shader);

    int status;
    glGetShaderiv(shader, GL_COMPILE_STATUS, &status);

    if (status == GL_FALSE) {
        char log[512];
        glGetShaderInfoLog(shader, 512, nullptr, log);
        std::cerr << "Error compiling shader '" << path << "' : " << log << std::endl;
    } else
        _shaders.push_back(shader);
}

void ShaderManager::validate()
{
    _validated = true;

    _program = glCreateProgram();

    for (const auto &s : _shaders)
        glAttachShader(_program, s);
    glLinkProgram(_program);
    glValidateProgram(_program);

    glUseProgram(_program);
}
