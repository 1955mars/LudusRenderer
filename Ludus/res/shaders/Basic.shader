#shader vertex
#version 330 core

layout(location = 0) in vec3 vPos;
layout(location = 1) in vec2 vTex;

uniform mat4 model;
uniform mat4 view;
uniform mat4 proj;

out vec2 texCoord;

void main()
{
    gl_Position = proj *  view * model * vec4(vPos, 1.0);
    texCoord = vTex;
}


#shader fragment
#version 330 core

in vec2 texCoord;

uniform sampler2D texture1;
uniform sampler2D texture2;

void main()
{
    gl_FragColor = mix(texture(texture1, texCoord), texture(texture2, texCoord), 0.2);
}