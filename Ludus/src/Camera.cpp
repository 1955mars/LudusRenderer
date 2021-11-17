#include "Camera.h"
#include "glm/gtc/quaternion.hpp"

#define GLM_ENABLE_EXPERIMENTAL
#include "glm/gtx/quaternion.hpp"

#define M_PI 3.14159f

Camera::Camera(const glm::mat4& projectionMatrix)
	:m_ProjectionMatrix(projectionMatrix)
{
	m_Position = { 0, 5, 5 };
	m_Rotation = glm::vec3(0, 0, 0);

	m_FocalPoint = glm::vec3(0.0f);
	m_Distance = glm::distance(m_Position, m_FocalPoint);

	m_Yaw = 3.0f * (float)M_PI / 4.0f;
	m_Pitch = M_PI / 4.0f;

	glm::quat orientation = glm::quat(glm::vec3(-m_Pitch, -m_Yaw, 0.0f));
	m_Rotation = glm::eulerAngles(orientation) * (180.0f / (float)M_PI);
	m_ViewMatrix = glm::translate(glm::mat4(1.0f), glm::vec3(0, 0, 1)) * glm::toMat4(glm::conjugate(orientation)) * glm::translate(glm::mat4(1.0f), -m_Position);
	m_ViewMatrix = glm::translate(glm::mat4(1.0f), m_Position) * glm::toMat4(orientation);
	m_ViewMatrix = glm::inverse(m_ViewMatrix);
}
