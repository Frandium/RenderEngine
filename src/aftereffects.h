#pragma once
#include "mesh.h"
#include "Shader.h"

class AfterEffects {
public:
	static AfterEffects* Instance();
	void UseCustomAfterEffectsShader(const std::string& vs, const std::string& fs);
	void UseDefaultAfterEffectsShader();
	void SetTextureBufferAsRenderTarget();
	void SetDefaultWindowAsRenderTarget();
private:
	AfterEffects();
	static AfterEffects* s_ins;
	std::shared_ptr<Mesh> screen_cover;
	GLuint fbo;
	GLuint screen_tex;
	GLuint rbo; // ������Ȼ����ģ�建��
	ShaderPtr default_shader;
	ShaderPtr current_shader;
};