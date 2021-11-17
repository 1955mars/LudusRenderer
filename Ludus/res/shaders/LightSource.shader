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

void main()
{
    gl_FragColor = vec4(1.0f);
}