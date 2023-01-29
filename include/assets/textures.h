#ifndef TEXTURES_CLASS_H
#define TEXTURES_CLASS_H

#include<glad/glad.h>
#include<GLFW/glfw3.h>
#include<iostream>
#include<stbi/stb_image.h>
#include"core/fs.h"

inline char texturePath[MAX_CWD+21];

struct Texture{
    GLuint id;
    int w, h;
    GLenum filter;
};

Texture loadTexture(const char*);

#endif