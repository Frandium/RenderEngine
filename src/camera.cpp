#include "camera.h"

CameraPtr Camera::s_ins = nullptr;
PROJECTION_MODE Camera::s_projection_mode = PERSPECTIVE;

Camera::Camera()
{
	m_position = glm::vec3(0, 0, 3);
	m_direction = glm::vec3(0, 0, -1);
	m_up = glm::vec3(0, 1, 0);
}

glm::mat4 Camera::GetProjectionMatrix() {
	glm::mat4 projection;
	if (s_projection_mode == PERSPECTIVE) {
		projection = glm::perspective(glm::radians(45.0f), Window::Instance()->Width() / Window::Instance()->Height(), .1f, 100.0f);
	}
	else if (s_projection_mode == ORTHOGONAL) {
		// TODO: 正交投影矩阵
	}
	return projection;
}

CameraPtr Camera::Instance() {
	if (s_ins == nullptr) {
		s_ins = new Camera();
	}
	return s_ins;
}

void Camera::Rotate(float yaw, float pitch) {
	m_pitch += pitch;
	if (m_pitch > 89.0f)
		m_pitch = 89.0f;
	if (m_pitch < -89.0f)
		m_pitch = -89.0f;
	m_yaw += yaw;
	m_direction.x = sin(glm::radians(m_yaw));
	m_direction.y = sin(glm::radians(m_pitch));
	m_direction.z = - cos(glm::radians(m_pitch)) * cos(glm::radians(m_yaw));
	m_direction = glm::normalize(m_direction);
}

void Camera::Translate(DIRECTION dir, float dis) {
	switch (dir)
	{
	case LEFT:
		m_position -= glm::normalize(glm::cross(m_direction, m_up)) * dis;
		break;
	case RIGHT:
		m_position += glm::normalize(glm::cross(m_direction, m_up)) * dis;
		break;
	case UP:
		m_position += m_up * dis;
		break;
	case DOWN:
		m_position -= m_up * dis;
		break;
	case FRONT:
		m_position += m_direction * dis;
		break;
	case BACK:
		m_position -= m_direction * dis;
		break;
	default:
		break;
	}
}