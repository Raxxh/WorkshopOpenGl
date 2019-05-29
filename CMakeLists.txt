cmake_minimum_required(VERSION 3.0)

add_executable(exec src/main.cpp src/AppWindow.cpp include/AppWindow.hpp)

target_link_libraries(exec GL GLEW glfw)
target_include_directories(exec PRIVATE include)
