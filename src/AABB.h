#pragma once
#include "raycasttarget.h"
#include "gameobject.h"
#include <memory>

class AABB;

typedef std::function<void(AABB*)> VisitAABBProc;
typedef std::function<void()> OnMouseClickCallBack;

class AABB: public RaycastTarget {
private:
	static std::list<AABB*> AABBs;
	glm::vec3 size;
	GameObjectPtr gameobject;
	
public :
	static void TraverseAABB(VisitAABBProc p);
	bool  IsHitted(const glm::vec3& origin,const glm::vec3& dir) override;
	inline GameObjectPtr GetGameObject() const { return gameobject; }
	AABB(GameObjectPtr const go, const glm::vec3& size);
	~AABB() {
		AABBs.remove(this);
	}
	OnMouseClickCallBack onClick;
};

typedef std::shared_ptr<AABB> AABBPtr;
