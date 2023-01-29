#version 330 core
layout (location = 0) in vec3 aPos;
layout (location = 1) in vec3 aNorm;
layout (location = 2) in vec2 aUV;

out vec3 norm;
out vec2 UV;

uniform mat4 camMatrix;
uniform mat4 objMatrix;

void main()
{
  gl_Position = camMatrix * objMatrix * vec4(aPos, 1.0f);
  norm = mat3(transpose(inverse(objMatrix))) * aNorm;
  UV = aUV;
}