#include <GL/glew.h>
#include "WindowManager.h"
#include <iostream>

WindowManager::~WindowManager() {
    glfwDestroyWindow(window);
    glfwTerminate();
}

bool WindowManager::initialize(int width, int height, const char* title) {
    if (!glfwInit()) {
        std::cerr << "Failed to initialize GLFW\n";
        return false;
    }

    window = glfwCreateWindow(width, height, title, nullptr, nullptr);
    if (!window) {
        std::cerr << "Failed to create GLFW window\n";
        glfwTerminate();
        return false;
    }

    glfwMakeContextCurrent(window);
    glewExperimental = GL_TRUE;
    if (glewInit() != GLEW_OK) {
        std::cerr << "Failed to initialize GLEW\n";
        return false;
    }

    return true;
}

bool WindowManager::shouldClose() const {
    return glfwWindowShouldClose(window);
}

void WindowManager::swapBuffers() {
    glfwSwapBuffers(window);
}

void WindowManager::pollEvents() {
    glfwPollEvents();
}

GLFWwindow* WindowManager::getWindow() const {
    return window;
}
