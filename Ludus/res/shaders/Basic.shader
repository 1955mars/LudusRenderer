#shader vertex
#version 330 core

layout(location = 0) in vec2 vPos;
layout(location = 1) in vec3 vCol;


out vec3 color;

void main()
{
    gl_Position = vec4(vPos, 0.0, 1.0);
    color = vCol;
}


#shader fragment
#version 330 core

in vec3 color;

void main()
{
    gl_FragColor = vec4(color, 1.0);
}