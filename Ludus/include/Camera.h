#pragma once

#include <glm/glm.hpp>

class Camera
{
public:
	Camera(const glm::mat4& projectionMatrix);

	const glm::mat4& GetProjectionMatrix() const { return m_ProjectionMatrix; }
	const glm::mat4& GetViewMatrix() const { return m_ViewMatrix; }

private:
	glm::mat4 m_ProjectionMatrix;
	glm::mat4 m_ViewMatrix;

	glm::vec3 m_Position;
	glm::vec3 m_Rotation;
	glm::vec3 m_FocalPoint;

	float m_Distance;

	float m_Pitch, m_Yaw;
};
