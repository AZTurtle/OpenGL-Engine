#version 330 core
layout (location = 0) in vec3 aPos;
layout (location = 1) in vec3 aNorm;

out vec3 norm;
out vec3 pos;

uniform mat4 viewMatrix;
uniform mat4 camMatrix;
uniform mat4 objMatrix;

void main()
{
  pos = vec3(objMatrix * vec4(aPos, 1.0f));
  gl_Position = viewMatrix * camMatrix * objMatrix * vec4(aPos, 1.0f);
  norm = mat3(transpose(inverse(objMatrix))) * aNorm;
}