#pragma once
#include <string>
#include <unordered_map>
#include <glm/glm.hpp>

class Shader
{
	struct ShaderSource
	{
		std::string VertexSource;
		std::string FragmentSource;
	};
public:
	Shader(const std::string& filePath);
	~Shader();
	void Bind();
	void Unbind();
	void SetUniform1i(const std::string& name, unsigned int v);
	void SetUniform1f(const std::string& name, float v);
	void SetUniform2f(const std::string& name, float v0, float v1);
	void SetUniform3f(const std::string& name, float v0, float v1, float v2);
	void SetUniform4f(const std::string& name, float v0, float v1, float v2, float v3);
	void SetUniformMat4f(const std::string& name, const glm::mat4& v);
private:
	ShaderSource ParseShader(const std::string& filePath);
	unsigned int CompileShader(unsigned int type, const std::string& source);
	void CreateShader();
	int GetUniformLocation(const std::string& name);
private:
	std::string m_FilePath;
	unsigned int m_RendererId;
	std::unordered_map<std::string, int> m_UniformMap;
};