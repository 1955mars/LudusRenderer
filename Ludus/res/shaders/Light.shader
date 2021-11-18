#shader vertex
#version 330 core

layout(location = 0) in vec3 vPosition;
layout(location = 1) in vec3 vNormal;
layout(location = 2) in vec2 vTex;

uniform mat4 model;
uniform mat4 view;
uniform mat4 proj;

out vec3 fragPos;
out vec3 normal;
out vec2 texCoord;

void main()
{
    gl_Position = proj * view * model * vec4(vPosition, 1.0);
    fragPos = vec3(model * vec4(vPosition, 1.0));
    normal = mat3(transpose(inverse(model))) * vNormal; //Transforming with normal matrix. Avoid doing this in shader. (CPU side is efficient)
    texCoord = vTex;
}


#shader fragment
#version 330 core

struct Material
{
    sampler2D diffuseMap;
    sampler2D specularMap;

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
in vec2 texCoord;

void main()
{
    //Ambient lighting
    vec3 ambient = vec3(texture(material.diffuseMap, texCoord)) * light.ambient;

    //Diffuse lighting
    vec3 norm = normalize(normal);
    vec3 lightDir = normalize(light.position - fragPos);
    float diff = max(dot(norm, lightDir), 0.0f);
    vec3 diffuse = vec3(texture(material.diffuseMap, texCoord)) * diff * light.diffuse;

    //Specular lighting
    vec3 viewDir = normalize(viewPos - fragPos);
    vec3 reflectDir = reflect(-lightDir, norm); //incoming light direction and normal vector
    float spec = pow(max(dot(viewDir, reflectDir), 0.0f), material.shininess);
    vec3 specular = vec3(texture(material.specularMap, texCoord)) * spec * light.specular;
    
    vec3 result = ambient + diffuse + specular;
    gl_FragColor = vec4(result, 1.0f);
}