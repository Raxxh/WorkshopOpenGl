/*
** EPITECH PROJECT, 2019
** Project
** File description:
** AppWindow.cpp
*/

#include <stdexcept>
#include <iostream>
#include <GL/glew.h>
#include "AppWindow.hpp"

AppWindow::AppWindow()
{
    if (!glfwInit())
        throw std::runtime_error("Failed to init glfw");

    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

    _window = glfwCreateWindow(640, 480, "Hello World", nullptr, nullptr);
    if (!_window) {
        glfwTerminate();
        throw std::runtime_error("Failed to create window");
    }
    glfwMakeContextCurrent(_window);

    std::cout << "OpenGl version : " << glGetString(GL_VERSION) << std::endl;

    auto glewInitResult = glewInit();
    if (glewInitResult != GLEW_OK) {
        glfwTerminate();

        throw std::runtime_error(std::string("glewInit")
                                     + (const char *) glewGetErrorString(
                                         glewInitResult));

    }
}

AppWindow::~AppWindow()
{
    glfwTerminate();
}

bool AppWindow::run()
{
    if (_firstFrame)
        _firstFrame = false;
    else {
        glfwSwapBuffers(_window);
        glfwPollEvents();
    }
    processInputs();
    if (glfwWindowShouldClose(_window))
        return false;
    glClear(GL_COLOR_BUFFER_BIT);
    return true;
}

void AppWindow::processInputs()
{
    if(glfwGetKey(_window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
        glfwSetWindowShouldClose(_window, true);

}
