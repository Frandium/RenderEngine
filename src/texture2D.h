#pragma once
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <iostream>

class Texture2D {
public:
	Texture2D(const std::string& texpath,  int index=0, bool alpha = false, bool reverse=true);
private:
	unsigned int m_texture;

};