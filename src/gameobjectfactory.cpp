#include "gameobjectfactory.h"

GameObjectMap GameObjectFactory::s_gomap = GameObjectMap();

GameObjectPtr GameObjectFactory::CreateGameObject(const std::string& name, ModelPtr model, ShaderPtr shader) {
	if (s_gomap.find(name) != s_gomap.end()) {
		std::cout << "ERROR: failed to create gameobject \'" << name << "\' : duplicate name." << std::endl;
		return nullptr;
	}
	GameObjectPtr go = std::make_shared<GameObject>(name, model, shader);
	s_gomap[name] = go;
	return go;
}

GameObjectPtr GameObjectFactory::FindByName(const std::string& name) {
	if (s_gomap.find(name) == s_gomap.end()) {
		std::cout << "ERROR: faild to find gameobject \'" << name << "\' : not exists." << std::endl;
		return nullptr;
	}
	return s_gomap[name];
}

void GameObjectFactory::DestroyGameObject(const std::string& name) {
	int r = s_gomap.erase(name);
	if(r==0)std::cout << "WARNING: try to destroy gameobject \'" << name << "\' : not exists." << std::endl;
}

void GameObjectFactory::RenderGameObject() {
	glm::mat4 view = Camera::Instance()->GetViewMatrix();
	glm::vec3 viewpos = Camera::Instance()->GetPosition();
	for (auto p : s_gomap) {
		if (p.second->IsActive()) {
			p.second->Render(view, viewpos);
			Window::Instance()->Render();
		}
	}
}