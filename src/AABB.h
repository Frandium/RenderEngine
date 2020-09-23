#pragma once
#include "raycasttarget.h"

class AABB: public RaycastTarget {
private:
	glm::vec3 offset;
	float minx;
	float maxx;
	float miny;
	float maxy;
	float minz;
	float maxz;

public :
	bool  IsHitted(glm::vec3 origin, glm::vec3 dir) override;
};