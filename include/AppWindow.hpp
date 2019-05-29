/*
** EPITECH PROJECT, 2019
** Project
** File description:
** AppWindow.hpp
*/

#pragma once

#include <GLFW/glfw3.h>

class AppWindow
{
public:
    AppWindow();
    ~AppWindow();

    bool run();

private:
    void processInputs();

private:
    GLFWwindow *_window;
    bool _firstFrame = true;
};


