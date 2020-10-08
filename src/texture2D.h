#pragma once
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <iostream>

class Texture2D {
public:
	// GL_TEXTURE0 保留给后处理，禁止使用
	Texture2D(const std::string& texpath,  GLuint index=1u, bool alpha = false, bool reverse=true);
private:
	unsigned int m_texture;

};