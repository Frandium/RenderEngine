#pragma once
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <iostream>
#include "input.h"

class Window {
public:
	static Window* Instance();
	static Window* Init(float w = 800, float h=600);
	GLFWwindow* glfwwindow() { return window; }
	void Render();
	void Clear();
	void Delete();
	inline void SetIndexCount(unsigned int i) { m_global_indices_count = i; }
	inline float Width() { return m_width; }
	inline float Height() { return m_height; }
private:
	Window(float w, float h);
	float m_width;
	float m_height;
	GLFWwindow* window;
	static Window* s_ins;
	unsigned int m_global_indices_count = 0;
};
