#pragma once
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <memory>
#include "mesh.h"


class Model {
public:
	Model(glm::vec3 position = glm::vec3(0, 0, 0), glm::vec3 rotation = glm::vec3(0, 0, 0), glm::vec3 scale = glm::vec3(1, 1, 1));
	glm::mat4 GetModelMatrix() const;
	inline glm::vec3 GetPosition() const { return m_position; }
	inline void SetMesh(std::shared_ptr<Mesh> mp) { mesh = mp; }
	bool SendToGPU() const;
	void Translate(glm::vec3 dir, float dis);
	void Rotate(glm::vec3 rotation);

private:
	glm::vec3 m_rotation;
	glm::vec3 m_position;
	glm::vec3 m_scale;
	std::shared_ptr<Mesh> mesh;
};

typedef std::shared_ptr<Model> ModelPtr;