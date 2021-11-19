#pragma once
#include <string>

class Texture
{
public:
	Texture(const std::string& path, const std::string& typeName = "texture_diffuse");
	~Texture();
	
	void Bind(unsigned int slot = 0) const;
	void Unbind() const;

	inline int GetWidth() const { return m_Width; };
	inline int GetHeight() const { return m_Height; }
	inline int GetBPP() const { return m_BPP; }
	inline std::string GetTypeName() const { return m_TypeName; }
	inline std::string GetFilePath() const { return m_FilePath; }
	inline unsigned int GetId() const { return m_RendererId; }

private:
	unsigned int m_RendererId;
	std::string m_TypeName;
	std::string m_FilePath;
	int m_Width, m_Height, m_BPP;
};