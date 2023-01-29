#ifndef WINDOW_CLASS_H
#define WINDOW_CLASS_H

#include<vector>
#include<iostream>
#include<glad/glad.h>
#include<GLFW/glfw3.h>
#include<glm/glm.hpp>
#include"camera.h"
#include"core/object.h"
#include"resources.h"
#include"assets/assets.h"
#include<functional>

class Window{
public:
    Window(int, int, int, int, const char*);
    virtual void update();
    virtual void draw() = 0;
    static void glLoadGlobalPointers();
    static std::vector<Window*> windows;
protected:
    int w, h, x, y;
    glm::mat4 camMat;
    GLFWwindow* window;
    const char* windowTitle;
    static Assets& assets;
    virtual void openWindow();
};

#endif