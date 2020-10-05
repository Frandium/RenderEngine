#include "model.h"
#include <iostream>

Model::Model(glm::vec3 position, glm::vec3 rotation, glm::vec3 scale):
	m_position(position),
	m_rotation(rotation),
	m_scale(scale)
{

}

glm::mat4x4 Model::GetModelMatrix() const {
	glm::mat4x4 model;
	model = glm::translate(model, m_position);
	model = glm::rotate(model, glm::radians(m_rotation.x), glm::vec3(1, 0, 0));
	model = glm::rotate(model, glm::radians(m_rotation.y), glm::vec3(0, 1, 0));
	model = glm::rotate(model, glm::radians(m_rotation.z), glm::vec3(0, 0, 1));
	model = glm::scale(model, m_scale);
	return model;
}

bool Model::SendToGPU() const {
	if (mesh == nullptr) {
		std::cout << "error: Try to render a model with no mesh binded." << std::endl;
		return false;
	}
	mesh->SendToGPU();
	return true;
}

void Model::Translate(glm::vec3 dir, float dis) {
	glm::vec3 normal_d = glm::normalize(dir);
	m_position += normal_d * dis;
}

void Model::Rotate(glm::vec3 rotation) {
	m_rotation += rotation;
//	m_rotation *= r;
}