#include <iostream>

#include "GlfwWindowSystem.h"

void error_callback(int error, const char* description) {
    fprintf(stderr, "Glfw callback error: %s\n", description);
}

static void key_callback(GLFWwindow* window, int key, int scancode, int action, int mods) {
    if (key == GLFW_KEY_ESCAPE && action == GLFW_PRESS) {
        glfwSetWindowShouldClose(window, GLFW_TRUE);
    }
}

GlfwWindowSystem::GlfwWindowSystem() {
    if (!glfwInit()) {
        std::cout << "GLFW: Initialization failed" << std::endl;
    }
    glfwSetErrorCallback(error_callback);

    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    this->window = glfwCreateWindow(800, 600, "Editor", NULL, NULL);
    if (!window) {
        std::cout << "GLFW Window or OpenGL context creation failed" << std::endl;
    }
    glfwMakeContextCurrent(window);
    glfwSetKeyCallback(window, key_callback);
    glfwSwapInterval(1);

    //testar, ta estranho essa sintaxe &this
    glfwGetFramebufferSize(window, &this->width, &this->height);
    glViewport(0, 0, width, height);

    // todo checar se deu erro de inicializacao do glew
    glewInit();
}

GlfwWindowSystem::~GlfwWindowSystem() {
    glfwDestroyWindow(window);
    glfwTerminate();
}

GLFWwindow* GlfwWindowSystem::GetWindow() {
    return this->window;
}

int GlfwWindowSystem::GetWidth() {
    return this->width;
}

int GlfwWindowSystem::GetHeight() {
    return this->height;
}
