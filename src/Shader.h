#pragma once
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <iostream>
#include <string>
#include <fstream>
#include <sstream>
#include <glm/glm.hpp>
#include <glm/gtc/type_ptr.hpp>


class Shader {
public:
	Shader(const std::string& vs, const std::string& fs);
	inline void Use() { glUseProgram(m_shader_program); }
	inline void Delete() { glDeleteProgram(m_shader_program); }
	void SetBool(const std::string& name, const bool b);
	void SetInt(const std::string& name, const int i);
	void SetFloat(const std::string& name, const float f);
	void SetVec4(const std::string& name, const glm::vec4& v);
	void SetVec3(const std::string& name, const glm::vec3& v);
	void SetMat4(const std::string& name, const glm::mat4& m);
private:
	unsigned int m_shader_program;
};


typedef std::shared_ptr<Shader> ShaderPtr;