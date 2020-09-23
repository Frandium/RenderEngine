#include "monobehaviour.h"

uint32_t MonoBehaviour::s_mono_count = 0;

std::unordered_map<uint32_t, MonoBehaviour*> MonoBehaviour::s_instances = std::unordered_map<uint32_t, MonoBehaviour*>();

MonoBehaviour::MonoBehaviour() {
	m_number = s_mono_count;
	s_instances[s_mono_count++] = this;
}

void MonoBehaviour::Traverse(visitMonoProc p) {
	for(auto mono : s_instances) {
		p(mono.second);
	}
}