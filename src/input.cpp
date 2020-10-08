#include "input.h"
#include "camera.h"
#include "AABB.h"

GLFWwindow* Input::s_window = nullptr;

void Input::TestMouseDown() {
	if (glfwGetMouseButton(s_window, GLFW_MOUSE_BUTTON_1) == GLFW_PRESS) {
		double x = 0, y = 0;
		glfwGetCursorPos(s_window, &x, &y);
//		std::cout << x << ' ' << y << std::endl;
		// 目前的视角，大概是水平方向 45°，竖直方向 35°
		float pitch = Camera::Instance()->GetPitch() + (y / Window::Instance()->Height() - 0.5) * 35;
		float yaw = Camera::Instance()->GetYaw() + (x / Window::Instance()->Width() - 0.5) * 45;
		float dirx = sin(glm::radians(yaw));
	    float diry = - sin(glm::radians(pitch));
		float dirz =  -cos(glm::radians(pitch)) * cos(glm::radians(yaw));
		std::cout << '(' << dirx << ',' << diry << ',' << dirz << ')' << std::endl;
		glm::vec3 direction = glm::normalize(glm::vec3(dirx, diry, dirz));
		auto test_raycast = [=](AABB* aabb)->void {
			if (aabb->IsRaycastEnabled() && aabb->IsHitted(Camera::Instance()->GetPosition(), direction)) {
				if (aabb->onClick != NULL) {
					aabb->onClick();
				}
			}
		};
		AABB::TraverseAABB(test_raycast);
	}
}