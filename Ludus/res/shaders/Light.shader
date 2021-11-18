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

struct Material
{
    vec3 ambient;
    vec3 diffuse;
    vec3 specular;

    float shininess;
};

struct Light
{
    vec3 position;

    vec3 ambient;
    vec3 diffuse;
    vec3 specular;
};

uniform vec3 viewPos;
uniform Material material;
uniform Light light;

in vec3 fragPos;
in vec3 normal;

void main()
{
    //Ambient lighting
    vec3 ambient = material.ambient * light.ambient;

    //Diffuse lighting
    vec3 norm = normalize(normal);
    vec3 lightDir = normalize(light.position - fragPos);
    float diff = max(dot(norm, lightDir), 0.0f);
    vec3 diffuse = (diff * material.diffuse) * light.diffuse;

    //Specular lighting
    vec3 viewDir = normalize(viewPos - fragPos);
    vec3 reflectDir = reflect(-lightDir, norm); //incoming light direction and normal vector
    float spec = pow(max(dot(viewDir, reflectDir), 0.0f), 256);
    vec3 specular = (spec * material.specular) * light.specular;
    
    vec3 result = ambient + diffuse + specular;
    gl_FragColor = vec4(result, 1.0f);
}