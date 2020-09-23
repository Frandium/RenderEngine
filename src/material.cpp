#include "Material.h"

void Material::UseShader() {
	shader->Use();
	for(auto p : paramTable) {
		shader->SetInt(p.first, p.second);
	}
}