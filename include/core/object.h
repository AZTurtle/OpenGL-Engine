#ifndef OBJECT_CLASS_H
#define OBJECT_CLASS_H

#include "assets/shaders.h"
#include "assets/model.h"
#include "assets/textures.h"
#include "glm/gtx/euler_angles.hpp"
#include "core/time_manager.h"

class Object{
    Model model;
    Shader_* shader;
    public:
        glm::mat4 transform = glm::mat4(1.0f);
        Object(Shader_*, Model);
        void render();
        void load();
};

#endif