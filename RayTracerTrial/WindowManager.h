#ifndef WINDOW_MANAGER_H
#define WINDOW_MANAGER_H

#include <GL/glew.h>
#include <GLFW/glfw3.h>

class WindowManager {
public:
    WindowManager() : window(nullptr) {}
    ~WindowManager();
    bool initialize(int width, int height, const char* title);
    bool shouldClose() const;
    void swapBuffers();
    void pollEvents();
    GLFWwindow* getWindow() const;

private:
    GLFWwindow* window;
};

#endif
