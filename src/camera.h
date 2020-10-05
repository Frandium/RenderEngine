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

	inline glm::mat4 GetViewMatrix() const { return glm::lookAt(m_position, m_position + m_direction, m_up); }
	inline glm::mat4 GetProjectionMatrix() const { return m_projection; }
	inline glm::vec3 GetPosition() const { return m_position; }
	inline glm::vec3 GetDirection() const { return m_direction; }
	inline float GetYaw() const { return m_yaw; }
	inline float GetPitch() const { return m_pitch; }
	glm::vec3 ScreenToWorldPoint(const glm::vec3& screen) const;
	void Rotate(float yaw,float pitch);
	void Translate(DIRECTION dir, float distance);
private:
	static CameraPtr s_ins;
	static PROJECTION_MODE s_projection_mode;

	Camera();

	glm::vec3 m_position;
	glm::vec3 m_direction;
	glm::vec3 m_up;

	glm::mat4 m_projection;

	float m_pitch = 0;
	float m_yaw = 0;
	
};