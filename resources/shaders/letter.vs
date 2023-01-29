#version 330 core
layout (location = 0) in vec3 aPos;
layout (location = 1) in vec3 aNorm;

uniform mat4 camMatrix;
uniform mat4 objMatrix;

void main()
{
  gl_Position = camMatrix * objMatrix * vec4(aPos, 1.0f);
}