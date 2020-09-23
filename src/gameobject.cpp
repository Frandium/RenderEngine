#include "gameobject.h"

GameObject::GameObject(std::string _name, ModelPtr _model, ShaderPtr _shader) :
	name(_name),
	model(_model),
	shader(_shader) {

}

void GameObject::Translate(glm::vec3 dir, float distance) {
	model->Translate(dir, distance);
	shader->Use();
	shader->SetMat4("model", model->GetModelMatrix());
}

void GameObject::Rotate(glm::vec3 rotation) {
	model->Rotate(rotation);
	shader->Use();
	shader->SetMat4("model", model->GetModelMatrix());
}

void GameObject::Render(const glm::mat4& view, const glm::vec3& viewpos) {
	model->SendToGPU();
	shader->Use();
	shader->SetMat4("view", view);
	shader->SetVec3("viewPos", viewpos);
}