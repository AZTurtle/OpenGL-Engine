#version 330 core
out vec4 FragColor;

uniform sampler2D tex;
uniform float color;

in vec2 UV;

void main()
{
   vec4 res = texture(tex, UV);
   FragColor = vec4(res.x * color, res.y * color, res.z * color, res.w);
}