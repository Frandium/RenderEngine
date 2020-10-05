#include "AABB.h"
#include <iostream>

std::list<AABB*> AABB::AABBs = std::list<AABB*>();

AABB::AABB(GameObjectPtr const go,const glm::vec3& _size):
	gameobject(go),
	size(_size)
{
	AABBs.push_back(this);
}

void AABB::TraverseAABB(VisitAABBProc p) {
	for (AABB* a : AABBs) {
		p(a);
	}
}

bool AABB::IsHitted(const glm::vec3& origin, const glm::vec3& dir) {
	glm::vec3 pos = gameobject->GetModel()->GetPosition();
	float minx = pos.x - size.x / 2;
	float maxx = pos.x + size.x / 2;
	float miny = pos.y - size.y / 2;
	float maxy = pos.y + size.y / 2;
	float minz = pos.z - size.z / 2;
	float maxz = pos.z + size.z / 2;
//	std::cout << minx << ' ' << maxx << ' ' << miny << ' ' << maxy << ' ' << minz << ' ' << maxz << std::endl;
	glm::vec3 norm_dir = glm::normalize(dir);

	// TODO: 以我朴素的思想，就是这样吧？
	// 网上各种AABB的碰撞检测没想明白，就按照自己想的写了
	if (dir.z != 0) {
		float t = (minz - origin.z) / norm_dir.z;
		if (t > 0) {
			float x = origin.x + t * norm_dir.x;
			float y = origin.y + t * norm_dir.y;
			if (minx < x && x < maxx && miny < y && y < maxy) return true;
		}

		t = (maxz - origin.z) / norm_dir.z;
		if (t > 0) {
			float x = origin.x + t * norm_dir.x;
			float y = origin.y + t * norm_dir.y;
			if (minx < x && x < maxx && miny < y && y < maxy) return true;
		}
	}

	if (dir.y != 0) {
		float t = (miny - origin.y) / norm_dir.y;
		if (t > 0) {
			float x = origin.x + t * norm_dir.x;
			float z = origin.z + t * norm_dir.z;
			if (minx < x && x < maxx && minz < z && z < maxz) return true;
		}

		t = (maxy - origin.y) / norm_dir.y;
		if (t > 0) {
			float x = origin.x + t * norm_dir.x;
			float z = origin.z + t * norm_dir.z;
			if (minx < x && x < maxx && minz < z && z < maxz) return true;
		}
	}

	if (dir.x != 0) {
		float t = (minx - origin.x) / norm_dir.x;
		if (t > 0) {
			float y = origin.y + t * norm_dir.y;
			float z = origin.z + t * norm_dir.z;
			if (miny < y && y < maxy && minz < z && z < maxz) return true;
		}

		t = (maxx - origin.x) / norm_dir.x;
		if (t > 0) {
			float y = origin.y + t * norm_dir.y;
			float z = origin.z + t * norm_dir.z;
			if (miny < y && y < maxy && minz < z && z < maxz) return true;
		}
	}

	return false;
}