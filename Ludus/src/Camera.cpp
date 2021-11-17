#include "Camera.h"
#include "glm/gtc/quaternion.hpp"

#define GLM_ENABLE_EXPERIMENTAL
#include "glm/gtx/quaternion.hpp"
#include "glm/gtx/string_cast.hpp"

#define M_PI 3.14159f

#include <iostream>

Camera::Camera(glm::vec3 _pos, glm::vec3 _up, float yaw, float pitch)
	:m_Position(_pos),
	m_WorldUp(_up),
	m_Yaw(yaw),
	m_Pitch(pitch),
	m_Front(glm::vec3(0.0f, 0.0f, -1.0f)),
	m_MovementSpeed(SPEED),
	m_MouseSensitivity(SENSITIVITY),
	m_Zoom(ZOOM)
{
	UpdateCameraVectors();
}


void Camera::ProcessKeyboard(CameraMovement direction, float deltaTime)
{
	float velocity = m_MovementSpeed * deltaTime;

	if (direction == CameraMovement::FORWARD)
		m_Position += m_Front * velocity;
	if (direction == CameraMovement::BACKWARD)
		m_Position -= m_Front * velocity;
	if (direction == CameraMovement::LEFT)
		m_Position -= m_Right * velocity;
	if (direction == CameraMovement::RIGHT)
		m_Position += m_Right * velocity;
}

void Camera::ProcessMouseMovement(float xOffset, float yOffset, bool constrainPitch)
{
	xOffset *= m_MouseSensitivity;
	yOffset *= m_MouseSensitivity;

	m_Yaw += xOffset;
	m_Pitch += yOffset;

	//If pitch is out of bounds, screen shouldn't be flipped
	if (constrainPitch)
	{
		if (m_Pitch > 89.0f)
			m_Pitch = 89.0f;
		if (m_Pitch < -89.0f)
			m_Pitch = -89.0f;
	}

	UpdateCameraVectors();
}

void Camera::ProcessMouseScroll(float yOffset)
{
	m_Zoom -= yOffset;
	if (m_Zoom < 1.0f)
		m_Zoom = 1.0f;
	if (m_Zoom > 45.0f)
		m_Zoom = 45.0f;
}


glm::mat4 Camera::GetViewMatrix()
{
	return glm::lookAt(m_Position, m_Position + m_Front, m_Up);
}

void Camera::UpdateCameraVectors()
{
	//New front vector
	glm::vec3 front;
	front.x = cos(glm::radians(m_Yaw)) * cos(glm::radians(m_Pitch));
	front.y = sin(glm::radians(m_Pitch));
	front.z = sin(glm::radians(m_Yaw)) * cos(glm::radians(m_Pitch));
	
	m_Front = glm::normalize(front);

	m_Right = glm::normalize(glm::cross(m_Front, m_WorldUp));
	m_Up = glm::normalize(glm::cross(m_Right, m_Front));
}
