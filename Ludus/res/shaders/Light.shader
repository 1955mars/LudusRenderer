#shader vertex
#version 330 core

layout(location = 0) in vec3 vPosition;
layout(location = 1) in vec3 vNormal;

uniform mat4 model;
uniform mat4 view;
uniform mat4 proj;

out vec3 fragPos;
out vec3 normal;

void main()
{
    gl_Position = proj * view * model * vec4(vPosition, 1.0);
    fragPos = vec3(model * vec4(vPosition, 1.0));
    normal = mat3(transpose(inverse(model))) * vNormal; //Transforming with normal matrix. Avoid doing this in shader. (CPU side is efficient)
    //normal = vNormal;
}


#shader fragment
#version 330 core

uniform vec3 viewPos;
uniform vec3 lightPos;
uniform vec3 lightColor;
uniform vec3 objectColor;

in vec3 fragPos;
in vec3 normal;

void main()
{
    //Ambient lighting
    float ambientStrength = 0.2f;
    vec3 ambient = ambientStrength * lightColor;

    //Diffuse lighting
    vec3 norm = normalize(normal);
    vec3 lightDir = normalize(lightPos - fragPos);
    float diff = max(dot(norm, lightDir), 0.0f);
    vec3 diffuse = diff * lightColor;

    //Specular lighting
    vec3 viewDir = normalize(viewPos - fragPos);
    vec3 reflectDir = reflect(-lightDir, norm); //incoming light direction and normal vector
    float spec = pow(max(dot(viewDir, reflectDir), 0.0f), 256);
    vec3 specular = spec * lightColor;
    
    vec3 result = (ambient + diffuse + specular) * objectColor;
    gl_FragColor = vec4(result, 1.0f);
}