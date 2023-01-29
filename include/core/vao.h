#ifndef VAO_CLASS_H
#define VAO_CLASS_H

#include<glad/glad.h>
#include<GLFW/glfw3.h>
#include<vector>
#include"assets/model.h"

class VAO{
    GLuint id, vbo, ebo;
    unsigned short attributeSize = 0;
    public:
        unsigned short indNum;
        VAO();

        template<typename T, typename i>
        VAO(std::vector<T> vertexBuffer, GLenum vertexDraw, std::vector<i> indexBuffer, GLenum indexDraw){
            glGenVertexArrays(1, &id);
            glGenBuffers(1, &vbo);
            glGenBuffers(1, &ebo);
            bindVertexBuffer(vertexBuffer, vertexDraw);
            bindIndexBuffer(indexBuffer, indexDraw);
        }

        void bind();
        void unbind();

        template<typename T>
        void bindVertexBuffer(std::vector<T> buffer, GLenum draw){
            bind();
            glBindBuffer(GL_ARRAY_BUFFER, vbo);

            glBufferData(GL_ARRAY_BUFFER, sizeof(T) * buffer.size(), buffer.data(), draw);
            
            unbind();
            glBindBuffer(GL_ARRAY_BUFFER, 0);
        }

        template<typename T>
        void bindVertexBuffer(T buffer[], size_t size, GLenum draw){
            bind();
            glBindBuffer(GL_ARRAY_BUFFER, vbo);
            
            glBufferData(GL_ARRAY_BUFFER, sizeof(T) * size, buffer, draw);
            
            unbind();
            glBindBuffer(GL_ARRAY_BUFFER, 0);
        }

        template<typename T>
        void bindIndexBuffer(std::vector<T> buffer, GLenum draw){
            bind();
            glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ebo);
            
            glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(T) * buffer.size(), buffer.data(), draw);
            
            unbind();
            glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
            
            indNum = buffer.size();
        }

        template<typename T>
        void bindIndexBuffer(T buffer[], size_t size, GLenum draw){
            bind();
            glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ebo);
            
            glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(T) * size, buffer, draw);
            
            unbind();
            glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
            
            indNum = size;
        }

        template<typename T>
        void addAttribute(unsigned short layout, unsigned short size, GLenum type, const void* offset){
            bind();
            glBindBuffer(GL_ARRAY_BUFFER, vbo);
            glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ebo);
            
            glVertexAttribPointer(layout, size, type, GL_FALSE, sizeof(T), offset);
            glEnableVertexAttribArray(layout);
            
            unbind();
            glBindBuffer(GL_ARRAY_BUFFER, 0);
            glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
        }

};

#endif