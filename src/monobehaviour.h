#pragma once
#include <unordered_map>
#include <functional>

class MonoBehaviour;

typedef std::function<void(MonoBehaviour*)> visitMonoProc;

class MonoBehaviour {
public:
	MonoBehaviour();
	virtual void Update() = 0;
	virtual void Init() = 0;
	static void Traverse(visitMonoProc);
	virtual ~MonoBehaviour() {};
private:
	static uint32_t s_mono_count;
	static std::unordered_map<uint32_t,MonoBehaviour*> s_instances;
	uint32_t m_number;
};