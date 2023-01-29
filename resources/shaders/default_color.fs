#version 330 core
out vec4 FragColor;

in vec3 norm;
in vec3 pos;

uniform vec3 camPos;

float upper(float x, float lim){
   if(x >= lim) return x;
   return 0;
}

vec3 light = vec3(1.0f, 0.6f, 1.0f);
vec3 global_light = normalize(vec3(0.3f, -1.0f, -0.3f));

void main()
{
   vec3 nNorm = normalize(norm);
   vec3 facing = normalize(light - pos);
   vec3 dir = normalize(camPos - pos);
   vec3 reflected = reflect(-facing, nNorm);

   FragColor = vec4(((vec3(pow(max(dot(dir, reflected), 0.0f), 2)) * 0.2f + 0.8f) * 
   max(dot(-nNorm, global_light), 0.0f) * 0.6f + 0.9f) * 
   vec3(0.3f, 0.8f, 0.5f), 1.0f);
}