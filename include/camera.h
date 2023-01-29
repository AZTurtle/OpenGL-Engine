#ifndef CAMERA_CLASS_H
#define CAMERA_CLASS_H
#include<glm/glm.hpp>
#include<glm/gtc/matrix_transform.hpp>
#include<glm/gtx/euler_angles.hpp>
#include<glm/gtc/type_ptr.hpp>
#include"core/time_manager.h"
#include"core/object.h"

inline glm::vec3 const UP_VECTOR(0.0f, 1.0f, 0.0f);

class Camera{
public:
    Camera();
    Camera(glm::vec3, glm::vec3, float, int*, int*, float);
    void update();
    void move(glm::vec3, glm::vec3);
    glm::mat4 transformMatrix;
    glm::mat4 viewMatrix;
    glm::mat4 matrix;
    glm::vec3 pos;
private:
    int* w;
    int* h;
    glm::vec3 rot;
    float FOV;
    float scale;
};



#endif