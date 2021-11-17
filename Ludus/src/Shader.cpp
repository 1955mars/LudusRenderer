#include "Shader.h"

#include <glad/glad.h>
#include <fstream>
#include <sstream>
#include <iostream>

Shader::Shader(const std::string& filePath)
	:m_FilePath(filePath)
{
	m_RendererId = glCreateProgram();
	CreateShader();
	Bind();
}

Shader::~Shader()
{
	glDeleteProgram(m_RendererId);
}

void Shader::Bind()
{
	glUseProgram(m_RendererId);
}

void Shader::Unbind()
{
	glUseProgram(0);
}

void Shader::SetUniform1i(const std::string& name, unsigned int v)
{
	glUniform1i(GetUniformLocation(name), v);
}

void Shader::SetUniform1f(const std::string& name, float v)
{
	glUniform1f(GetUniformLocation(name), v);
}

void Shader::SetUniform2f(const std::string& name, float v0, float v1)
{
	glUniform2f(GetUniformLocation(name), v0, v1);
}

void Shader::SetUniform3f(const std::string& name, float v0, float v1, float v2)
{
	glUniform3f(GetUniformLocation(name), v0, v1, v2);
}

void Shader::SetUniform4f(const std::string& name, float v0, float v1, float v2, float v3)
{
	glUniform4f(GetUniformLocation(name), v0, v1, v2, v3);
}

void Shader::SetUniformMat4f(const std::string& name, const glm::mat4& v)
{
	glUniformMatrix4fv(GetUniformLocation(name), 1, GL_FALSE, &v[0][0]);
}

Shader::ShaderSource Shader::ParseShader(const std::string& filePath)
{
    std::ifstream stream(filePath);
    std::string line;

    enum class ShaderType
    {
        NONE = -1, VERTEX = 0, FRAGMENT = 1
    };

    std::stringstream ss[2];
    ShaderType type = ShaderType::NONE;

    while (std::getline(stream, line))
    {
        if (line.find("#shader") != line.npos)
        {
            if (line.find("vertex") != line.npos)
                type = ShaderType::VERTEX;
            else if (line.find("fragment") != line.npos)
                type = ShaderType::FRAGMENT;
        }
        else
        {
            ss[(int)type] << line << "\n";
        }
    }

    return { ss[0].str(), ss[1].str() };
}

unsigned int Shader::CompileShader(unsigned int type, const std::string& source)
{
    unsigned int id = glCreateShader(type);
    const char* src = source.c_str();
    glShaderSource(id, 1, &src, nullptr);
    glCompileShader(id);

    return id;
}

void Shader::CreateShader()
{
    ShaderSource source = ParseShader(m_FilePath);

    unsigned int vs = CompileShader(GL_VERTEX_SHADER, source.VertexSource);
    unsigned int fs = CompileShader(GL_FRAGMENT_SHADER, source.FragmentSource);

    glAttachShader(m_RendererId, vs);
    glAttachShader(m_RendererId, fs);

    glLinkProgram(m_RendererId);
    glValidateProgram(m_RendererId);

    glDeleteShader(vs);
    glDeleteShader(fs);
}

int Shader::GetUniformLocation(const std::string& name)
{
    if (m_UniformMap.find(name) != m_UniformMap.end())
        return m_UniformMap[name];

    int location = glGetUniformLocation(m_RendererId, name.c_str());

    if (location == -1)
        std::cout << "Location for Uniform " << name << " doesn't exist!\n";

    m_UniformMap[name] = location;

    return location;
}
