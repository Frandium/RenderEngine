#pragma once
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <vector>
#include <memory>
#include "window.h"

typedef std::shared_ptr<std::vector<float>> verticesPtr;
typedef std::shared_ptr<std::vector<unsigned int>> indicesPtr;
typedef std::shared_ptr<std::vector<float>> uvPtr;
typedef std::shared_ptr<std::vector<float>> normalPtr;

class Mesh {
public:
    static std::shared_ptr<Mesh> GetCube();
    static std::shared_ptr<Mesh> GetPlane();

    Mesh();
    Mesh(verticesPtr vertices, indicesPtr indices, uvPtr uv, normalPtr normals);
    void SendToGPU();
    inline void Delete() { glDeleteBuffers(1, &m_VBO); glDeleteBuffers(1, &m_EBO); glDeleteVertexArrays(1, &m_VAO);}
private:
    static std::shared_ptr<Mesh> cube;
    static std::shared_ptr<Mesh> plane;

    verticesPtr m_vertices;
    indicesPtr m_indices;
    uvPtr m_uv;
    normalPtr m_normals;
    uint16_t m_icount;
    uint16_t m_vcount;
    unsigned int m_VBO;
    unsigned int m_EBO;
    unsigned int m_VAO;
    unsigned int m_uvBuffer;
    unsigned int m_normBuffer;
};