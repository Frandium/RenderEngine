#pragma once
#include "Shader.h"
#include <memory>
#include <unordered_map>

class Material {
public:
	void UseShader();
private:
	std::shared_ptr<Shader> shader;
	std::unordered_map<std::string, int> paramTable;
};