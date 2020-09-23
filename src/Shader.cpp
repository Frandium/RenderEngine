#include "Shader.h"


Shader::Shader(const std::string& vs, const std::string& fs) {
    // TODO：根据输入的文件路径读取文件内容，编译 shader
    std::string vertexCode;
    std::string fragmentCode;
    std::ifstream vShaderFile;
    std::ifstream fShaderFile;
    // 保证ifstream对象可以抛出异常：
    vShaderFile.exceptions(std::ifstream::failbit | std::ifstream::badbit);
    fShaderFile.exceptions(std::ifstream::failbit | std::ifstream::badbit);
    try
    {
        // 打开文件
        vShaderFile.open(vs);
        fShaderFile.open(fs);
        std::stringstream vShaderStream, fShaderStream;
        // 读取文件的缓冲内容到数据流中
        vShaderStream << vShaderFile.rdbuf();
        fShaderStream << fShaderFile.rdbuf();
        // 关闭文件处理器
        vShaderFile.close();
        fShaderFile.close();
        // 转换数据流到string
        vertexCode = vShaderStream.str();
        fragmentCode = fShaderStream.str();
    }
    catch (std::ifstream::failure e)
    {
        std::cout << "error: failed to read shader" << std::endl;
    }
    const char* vertexShaderSource = vertexCode.c_str();
    const char* fragmentShaderSource = fragmentCode.c_str();

    unsigned int vertexShader;
    vertexShader = glCreateShader(GL_VERTEX_SHADER);
    glShaderSource(vertexShader, 1, &vertexShaderSource, NULL);
    glCompileShader(vertexShader);
    int success;
    char infoLog[512];
    glGetShaderiv(vertexShader, GL_COMPILE_STATUS, &success);
    if (!success)
    {
        glGetShaderInfoLog(vertexShader, 512, NULL, infoLog);
        std::cout << "error: Failed to compile shader " << vs << infoLog << std::endl;
    }

    unsigned int fragmentShader;
    fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
    glShaderSource(fragmentShader, 1, &fragmentShaderSource, NULL);
    glCompileShader(fragmentShader);
    glGetShaderiv(fragmentShader, GL_COMPILE_STATUS, &success);
    if (!success)
    {
        glGetShaderInfoLog(fragmentShader, 512, NULL, infoLog);
        std::cout << "error: Failed to compile shader " << fs << infoLog << std::endl;
    }

    m_shader_program = glCreateProgram();
    glAttachShader(m_shader_program, vertexShader);
    glAttachShader(m_shader_program, fragmentShader);
    // link the output of vs to the input of fs
    glLinkProgram(m_shader_program);
    glGetProgramiv(m_shader_program, GL_LINK_STATUS, &success);
    if (!success) {
        glGetProgramInfoLog(m_shader_program, 512, NULL, infoLog);
        std::cout << "error: Faild to link shaders" << infoLog << std::endl;
    }
    glDeleteShader(vertexShader);
    glDeleteShader(fragmentShader);
}

void Shader::SetBool(const std::string& name, const bool b) {
    glUniform1i(glGetUniformLocation(m_shader_program, name.c_str()), (int)b);
}

void Shader::SetInt(const std::string& name, const int i) {
    glUniform1i(glGetUniformLocation(m_shader_program, name.c_str()), i);
}

void Shader::SetFloat(const std::string& name, const float f) {
    glUniform1f(glGetUniformLocation(m_shader_program, name.c_str()), f);
}

void Shader::SetVec3(const std::string& name, const glm::vec3& v) {
    glUniform3f(glGetUniformLocation(m_shader_program, name.c_str()), v.r, v.g, v.b);
}

void Shader::SetVec4(const std::string& name, const glm::vec4& v) {
    glUniform4f(glGetUniformLocation(m_shader_program, name.c_str()), v.r, v.g, v.b, v.a);
}

void Shader::SetMat4(const std::string& name, const glm::mat4& m) {
    glUniformMatrix4fv(glGetUniformLocation(m_shader_program, name.c_str()), 1, GL_FALSE, glm::value_ptr(m));
}