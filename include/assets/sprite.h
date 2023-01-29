#ifndef SPRITE_CLASS_H
#define SPRITE_CLASS_H

#include"assets/assets.h"
#include"resources.h"
#include"core/vao.h"
#include"camera.h"

inline const unsigned short INDS[] = {
    0,3,2,
    2,1,0
};

class Sprite{
    Texture* img;
    Vert_T_2D verts[4];
    Shader_* shader;
    VAO vao;
    public:
        Sprite(const char*, glm::mat4*, Camera*, float*);
        void draw();
};

#endif