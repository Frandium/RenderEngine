#pragma once
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include "monobehaviour.h"

class GameTime: MonoBehaviour{
public:
	static inline float DeltaTime() { return s_last_time - s_last_last_time; };
	virtual void Update() override;
	virtual void Init() override;
private:
	static float s_last_time;
	static float s_last_last_time;
};