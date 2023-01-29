#include"core/vao.h"

VAO::VAO(){
    glGenVertexArrays(1, &id);
    glGenBuffers(1, &vbo);
    glGenBuffers(1, &ebo);
}

void VAO::bind(){
    glBindVertexArray(id);
}

void VAO::unbind(){
    glBindVertexArray(0);
}