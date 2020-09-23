#pragma once
#include <memory>
#include <string>
#include "model.h"
#include "monobehaviour.h"
#include "Shader.h"

class GameObject;
typedef std::unordered_map<std::string, std::shared_ptr<GameObject>> GameObjectMap;
typedef std::shared_ptr<GameObject> GameObjectPtr;

class GameObject {
public:
	GameObject(std::string _name, ModelPtr _model, ShaderPtr _shader);
	void Translate(glm::vec3 direction, float distance);
	void Rotate(glm::vec3 rotation);
	void Render(const glm::mat4& view, const glm::vec3& viewpos);
	inline void SetActive(bool b) { active = b; }
	inline bool IsActive() { return active; }
private:
	std::string name; // ÎïÌåÃû×Ö
	ModelPtr model;
	ShaderPtr shader;
	bool active = true;
};