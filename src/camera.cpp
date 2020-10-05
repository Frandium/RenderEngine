#include "camera.h"

CameraPtr Camera::s_ins = nullptr;
PROJECTION_MODE Camera::s_projection_mode = PERSPECTIVE;

Camera::Camera()
{
	m_position = glm::vec3(0, 0, 10);
	m_direction = glm::vec3(0, 0, -1);
	m_up = glm::vec3(0, 1, 0);
	if (s_projection_mode == PERSPECTIVE) {
		m_projection = glm::perspective(glm::radians(45.0f), Window::Instance()->Width() / Window::Instance()->Height(), .1f, 100.0f);
	}
	else if (s_projection_mode == ORTHOGONAL) {
		// TODO: 正交投影矩阵
	}
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

	// 其实你的屏幕某点发射的射线只和 pitch 和 yaw 有关，所以你只需要把 screen 对应的角度算出来就完事儿了！
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

glm::vec3 Camera::ScreenToWorldPoint(const glm::vec3& screen) const {
	// 摄像机 (0, 0, 10)时，z=0 的平面上 70 个像素相当于 1 长度。
	// 摄像机 (0, 0, 10)时，z=5 的平面上 140 个像素相当于 1 长度。
	// 近平面是0.1
	const float camera_distance = 10;
	const float pixel_per_length = 70;
	const float mult = camera_distance * pixel_per_length;


	return glm::vec3(0);
}