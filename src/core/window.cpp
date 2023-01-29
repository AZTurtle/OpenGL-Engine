#include"core/window.h"

std::vector<Window*> Window::windows;
Assets& Window::assets = Assets::getAssets();

Window::Window(int x, int y, int w, int h, const char* windowTitle){
    this->w = w;
    this->h = h;
    this->x = x;
    this->y = y;
    this->windowTitle = windowTitle;
    if(windows.size() == 0){
        this->window = glfwCreateWindow(w, h, windowTitle, NULL, NULL);
        glfwMakeContextCurrent(window);
        gladLoadGL();
        glLoadGlobalPointers();
    } else {
        this->window = glfwCreateWindow(w, h, windowTitle, NULL, windows[0]->window);
        glfwMakeContextCurrent(window);
    }
    if(window == NULL){
        std::cout << windowTitle << " failed" << std::endl;
    }
    windows.push_back(this);
}

void Window::update(){
    if(glfwWindowShouldClose(window)){
        for(std::vector<Window*>::iterator i = windows.begin(); i != windows.end(); i++){
            if(this == *i){
                windows.erase(i);
                glfwDestroyWindow(window);
                break;
            }
        }
    }
}

void Window::openWindow(){
    glfwShowWindow(window);
}