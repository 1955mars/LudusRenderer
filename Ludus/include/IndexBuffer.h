#pragma once


class IndexBuffer
{
public:
	IndexBuffer(const unsigned int* data, unsigned int count);
	~IndexBuffer();
	void Bind() const;
	void Unbind() const;

	unsigned int GetElementCount() const { return m_Count; }

private:
	unsigned int m_RendererId;
	unsigned int m_Count;
};