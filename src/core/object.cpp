#include"core/object.h"

Object::Object(Shader_* shader, Model model) : shader(shader), model(model) {}

void Object::render(){
    shader->bind();
    model.render();
}

void Object::load(){
    
}