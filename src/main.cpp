#define STB_IMAGE_IMPLEMENTATION
#include<stdio.h>
#include<iostream>
#include"mainWindow.h"
#include<direct.h>
#include"core/time_manager.h"
#include"core/input.h"
#include"core/fs.h"

void Window::glLoadGlobalPointers(){
    Assets& assets = Assets::getAssets();
    assets.load();
}

int main(){
    getcwd(CWD, MAX_CWD);
    getFilePath(modelPath,"\\resources\\models\\");
    getFilePath(texturePath, "\\resources\\textures\\");
    getFilePath(shaderPath, "\\resources\\shaders\\");

    glfwInit();
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
    glfwWindowHint(GLFW_VISIBLE, GLFW_FALSE);

    stbi_set_flip_vertically_on_load(true);

    MainWindow mainWindow(0, 0, 800, 800, "App");

    mainWindow.load();

    mainWindow.openWindow();
    
    while(Window::windows.size() > 0){
        update_time();
        getInputInfo();
        for(Window* window : Window::windows){ 
            window->update();
        }
        glfwPollEvents();
    }

    glfwTerminate();
    return 0;
}