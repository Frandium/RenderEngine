#include "aftereffects.h"
#include "window.h"

AfterEffects* AfterEffects::s_ins = nullptr;

AfterEffects* AfterEffects::Instance() {
	if (s_ins == nullptr) {
		s_ins = new AfterEffects();
	}
	return s_ins;
}

AfterEffects::AfterEffects() {
	if (default_shader == nullptr) {
		// ���ɸ�����Ļ�� mesh
		screen_cover = Mesh::GetPlane();
		default_shader = std::make_shared<Shader>("shader/default_after_effects.vs", "shader/default_after_effects.fs");
		default_shader->Use();
		default_shader->SetInt("MainTex", 0);
		current_shader = default_shader;

		// ������ fbo
		glGenFramebuffers(1, &fbo);
		glBindFramebuffer(GL_FRAMEBUFFER, fbo);

		//Ϊ fbo ��������
		glGenTextures(1, &screen_tex);
		glActiveTexture(GL_TEXTURE0);
		glBindTexture(GL_TEXTURE_2D, screen_tex);
		glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, Window::Instance()->Width(), Window::Instance()->Height(),0, GL_RGB, GL_UNSIGNED_BYTE, NULL);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
		glBindTexture(GL_TEXTURE_2D, 0);

		// ������󶨵� fbo ����ɫ���� 0 ������Ⱦ����ȴ洢�� tex ����ȥ
		glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_TEXTURE_2D, screen_tex, 0);

		// ���� rbo�����ڴ洢��Ⱥ�ģ��
		glGenRenderbuffers(1, &rbo);
		glBindRenderbuffer(GL_RENDERBUFFER, rbo);
		glRenderbufferStorage(GL_RENDERBUFFER, GL_DEPTH24_STENCIL8, Window::Instance()->Width(), Window::Instance()->Height());
		glBindRenderbuffer(GL_RENDERBUFFER, 0);

		// ����Ⱥ�ģ�建��󶨸�֡����
		glFramebufferRenderbuffer(GL_FRAMEBUFFER, GL_DEPTH_STENCIL_ATTACHMENT, GL_RENDERBUFFER, rbo);

		// ���֡����������
		if (glCheckFramebufferStatus(GL_FRAMEBUFFER) != GL_FRAMEBUFFER_COMPLETE) {
			std::cout << " After effects frame buffer error." << std::endl;
		}
		else {
			std::cout << "After effects initiation succeded." << std::endl;
		}

		//���
		glBindFramebuffer(GL_FRAMEBUFFER, 0);

	}
}

void AfterEffects::UseCustomAfterEffectsShader(const std::string& vs, const std::string& fs) {
	current_shader = std::make_shared<Shader>(vs, fs);
}

void AfterEffects::UseDefaultAfterEffectsShader() {
	current_shader = default_shader;
}

void AfterEffects::SetTextureBufferAsRenderTarget() {
	glBindFramebuffer(GL_FRAMEBUFFER, fbo);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glEnable(GL_DEPTH_TEST);
}

void AfterEffects::SetDefaultWindowAsRenderTarget() {
	glBindFramebuffer(GL_FRAMEBUFFER, 0);
	glClear(GL_COLOR_BUFFER_BIT);
	current_shader->Use();
	screen_cover->SendToGPU();
	glDisable(GL_DEPTH_TEST);
	glBindTexture(GL_TEXTURE_2D, screen_tex);
	Window::Instance()->Render();
}

