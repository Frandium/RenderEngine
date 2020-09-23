#pragma once
#include "gameobject.h"
#include "camera.h"

class GameObjectFactory {
public:
	static GameObjectPtr CreateGameObject(const std::string& name, ModelPtr model, ShaderPtr shader);
	static GameObjectPtr FindByName(const std::string& name);
	static void DestroyGameObject(const std::string& name);
	static void RenderGameObject();
private:
	static GameObjectMap s_gomap;
};