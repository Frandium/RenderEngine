#pragma once
#include <glm/glm.hpp>

class RaycastTarget {
protected:
	bool raycastEnabled = true;

public:
	inline void SetRaycastEnabled(bool b) { raycastEnabled = b; }
	inline bool IsRaycastEnabled() { return raycastEnabled; }
	virtual bool IsHitted(const glm::vec3& origin,const glm::vec3& dir) = 0;
};