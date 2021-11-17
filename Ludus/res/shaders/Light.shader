#shader vertex
#version 330 core

layout(location = 0) in vec3 vPos;
layout(location = 1) in vec2 vTex;

uniform mat4 model;
uniform mat4 view;
uniform mat4 proj;


void main()
{
    gl_Position = proj * view * model * vec4(vPos, 1.0);
}


#shader fragment
#version 330 core

uniform vec3 lightColor;
uniform vec3 objectColor;

void main()
{
    float ambientStrength = 0.2f;
    vec3 ambient = ambientStrength * lightColor;

    gl_FragColor = vec4(ambient * objectColor, 1.0f);
}