#include"camera.h"

Camera::Camera(glm::vec3 pos, glm::vec3 rot, float FOV, int* w, int* h, float scale){
    this->pos = pos;
    this->rot = rot;
    this->w = w;
    this->h = h;
    this->FOV = FOV;
    this->scale = scale;
    update();
}

void Camera::update(){
    transformMatrix = glm::lookAt(pos, pos+rot, UP_VECTOR);
    viewMatrix = glm::perspective(glm::radians(FOV), (float)*w / (float)*h, 0.1f, 100.0f);
    matrix = viewMatrix * transformMatrix;
}

void Camera::move(glm::vec3 pos, glm::vec3 rot){
    this->pos = pos;
    this->rot = rot;
}