#version 330 core
layout (location = 0) in vec2 aPos;
layout (location = 1) in vec2 aUV;

out vec2 UV;

uniform mat4 matrix;

void main()
{
  gl_Position = matrix * vec4(aPos, 0.0f, 1.0f);
  UV = aUV;
}