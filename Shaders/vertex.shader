#version 330 core

layout(location = 0) in vec2 pos;
layout(location = 1) in vec4 col;

out vec4 myColor;

void main()
{
    gl_Position = vec4(pos.x, pos.y, 0.0, 1.0);
    myColor = col;
}
