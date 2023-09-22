#pragma once

#define GLFW_INCLUDE_NONE
#include <GLFW/glfw3.h>

#define GLEW_STATIC
#include <GL/glew.h>

class GlfwWindowSystem {
public:
    GlfwWindowSystem();
    ~GlfwWindowSystem();

    GLFWwindow* GetWindow();
    int GetWidth();
    int GetHeight();
private:
    GLFWwindow* window;

    int width; 
    int height;
};

