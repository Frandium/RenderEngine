#pragma once
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <iostream>
#include <string>
#include "window.h"
#include "texture2D.h"
#include "input.h"
#include "monobehaviour.h"
#include "camera.h"
#include "gameobjectfactory.h"
#include "AABB.h"

class ShaderToy : protected MonoBehaviour {
public:
	ShaderToy() {  };
	~ShaderToy() {};
	virtual void Update() override;
	virtual void Init() override;
private:
	GameObjectPtr cubego;
	AABBPtr cubeaabb;
	GameObjectPtr lightgo;
	CameraPtr main_camera;
	float lasttime;
	float camera_speed = 5;
};