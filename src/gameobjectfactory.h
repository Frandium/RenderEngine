#pragma once
#include "gameobject.h"
#include <functional>

typedef std::function<void(GameObjectPtr)> VisitGameObjectProc;

class GameObjectFactory {
public:
	static GameObjectPtr CreateGameObject(const std::string& name, ModelPtr model, ShaderPtr shader);
	static GameObjectPtr FindByName(const std::string& name);
	static void DestroyGameObject(const std::string& name);
	static void RenderGameObject();
	static void TraverseGameObject(const VisitGameObjectProc);
private:
	static GameObjectMap s_gomap;
};