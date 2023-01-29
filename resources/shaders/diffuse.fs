#version 330 core
out vec4 FragColor;

in vec3 norm;
uniform vec3 color;

void main()
{
    float comp = dot(-normalize(norm), vec3(0.0f, -1.0f, -0.2f));
    FragColor = vec4(color * (max(comp, 0.4f) * 0.5f + 0.5f), 1.0f);
}