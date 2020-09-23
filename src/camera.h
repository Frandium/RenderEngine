#pragma once
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include "window.h"

enum PROJECTION_MODE {
	PERSPECTIVE,
	ORTHOGONAL
};

enum DIRECTION {
	LEFT,
	RIGHT,
	UP,
	DOWN,
	FRONT,
	BACK
};

class Camera;
typedef Camera* CameraPtr;

class Camera {
public:
	static void SetProjectionMode(PROJECTION_MODE pm) { s_projection_mode = pm; }
	static CameraPtr Instance();

	inline glm::mat4 GetViewMatrix() { return glm::lookAt(m_position, m_position + m_direction, m_up); }
	glm::mat4 GetProjectionMatrix();
	inline glm::vec3 GetPosition() { return m_position; }
	void Rotate(float yaw,float pitch);
	void Translate(DIRECTION dir, float distance);
private:
	static CameraPtr s_ins;
	static PROJECTION_MODE s_projection_mode;

	Camera();

	glm::vec3 m_position;
	glm::vec3 m_direction;
	glm::vec3 m_up;

	float m_pitch = 0;
	float m_yaw = 0;
	
};