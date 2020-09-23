#pragma once
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <iostream>
#include <string>
#include "window.h"
#include "Shader.h"
#include "mesh.h"
#include "input.h"
#include "monobehaviour.h"
#include "texture2D.h"
#include "camera.h"
#include "model.h"
#include "gameobject.h"
#include "gameobjectfactory.h"

class ShaderToy : protected MonoBehaviour {
public:
	ShaderToy() {  };
	~ShaderToy() {};
	virtual void Update() override;
	virtual void Init() override;
private:
	GameObjectPtr cubego;
	GameObjectPtr lightgo;
	CameraPtr main_camera;
	float lasttime;
	float camera_speed = 5;
};