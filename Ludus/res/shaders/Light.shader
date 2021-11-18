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

struct DirLight
{
    vec3 direction;

    vec3 ambient;
    vec3 diffuse;
    vec3 specular;
};

struct PointLight
{
    vec3 position;

    vec3 ambient;
    vec3 diffuse;
    vec3 specular;

    float constant;
    float linear;
    float quadratic;
};

#define NR_POINT_LIGHTS 1

uniform vec3 viewPos;
uniform Material material;
uniform DirLight dirLight;
uniform PointLight pointLights[NR_POINT_LIGHTS];

in vec3 fragPos;
in vec3 normal;
in vec2 texCoord;

vec3 CalculateDirLight(DirLight light, vec3 normal, vec3 viewDir)
{
    vec3 lightDir = normalize(-light.direction);

    float diff = max(dot(lightDir, normal), 0.0f);
    
    vec3 reflectDir = reflect(-lightDir, normal);
    float spec = pow(max(dot(reflectDir, viewDir), 0.0f), material.shininess);

    vec3 ambient = light.ambient * vec3(texture(material.diffuseMap, texCoord));
    vec3 diffuse = light.diffuse * vec3(texture(material.diffuseMap, texCoord)) * diff;
    vec3 specular = light.specular * vec3(texture(material.specularMap, texCoord)) * spec;

    return (ambient + diffuse + specular);
}

vec3 CalculatePointLight(PointLight light, vec3 normal, vec3 viewDir)
{
    vec3 lightDir = normalize(light.position - fragPos);

    float diff = max(dot(lightDir, normal), 0.0f);

    vec3 reflectDir = reflect(-lightDir, normal);
    float spec = pow(max(dot(reflectDir, viewDir), 0.0f), material.shininess);

    float distance = length(light.position - fragPos);
    float attenuation = 1.0 / (light.constant + light.linear * distance + light.quadratic * (distance * distance));

    vec3 ambient = light.ambient * vec3(texture(material.diffuseMap, texCoord));
    vec3 diffuse = light.diffuse * vec3(texture(material.diffuseMap, texCoord)) * diff;
    vec3 specular = light.specular * vec3(texture(material.specularMap, texCoord)) * spec;

    return (ambient + diffuse + specular) * attenuation;
}

void main()
{
    //properties
    vec3 norm = normalize(normal);
    vec3 viewDir = normalize(viewPos - fragPos);
    
    vec3 result = CalculateDirLight(dirLight, norm, viewDir);

    for (int i = 0; i < NR_POINT_LIGHTS; i++)
        result += CalculatePointLight(pointLights[i], norm, viewDir);
    
    gl_FragColor = vec4(result, 1.0f);
}