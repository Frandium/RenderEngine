#pragma once
#include <glad/glad.h>
#include <GLFW/glfw3.h>

class Input {
public:
	static inline bool GetKeyDown(int key) {
		return glfwGetKey(s_window, key) == GLFW_PRESS;
	}
	static void SetWindow(GLFWwindow* w) { s_window = w; }
private:
	static GLFWwindow* s_window;

};