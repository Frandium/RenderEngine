#include "mesh.h"
#include "window.h"

Mesh::Mesh() {
    verticesPtr vp = std::make_shared<std::vector<float>>(std::vector<float>({
        -.5f,  .5f,  0,
        -.5f, -.5f, 0,
         .5f, -.5f,  0,
         .5f,  .5f,  0
        }));
    
    indicesPtr ip = std::make_shared<std::vector<unsigned int>>(std::vector<unsigned int>({ 
        0, 1, 2,
        0, 2, 3
        }));

    uvPtr uvp = std::make_shared<std::vector<float>>(std::vector<float>({
        0, 1,
        0, 0,
        1, 0,
        1, 1
        }));

    normalPtr np = std::make_shared<std::vector<float>>(std::vector<float>({
        0, 0, 1,
        0, 0, 1,
        0, 0, 1,
        0, 0, 1
        }));

    Mesh(vp, ip, uvp, np);
}

Mesh::Mesh(verticesPtr vertices, indicesPtr indices, uvPtr uv, normalPtr normals):
    m_vertices(vertices),
    m_indices(indices),
    m_uv(uv),
    m_normals(normals),
    m_vcount(vertices->size() / 3),
    m_icount(indices->size())
{
    std::cout << "load mesh" << std::endl;
    glGenVertexArrays(1, &m_VAO);
    glBindVertexArray(m_VAO);
    glGenBuffers(1, &m_VBO);
    glGenBuffers(1, &m_EBO);
    glGenBuffers(1, &m_uvBuffer);
    glGenBuffers(1, &m_normBuffer);

    glBindBuffer(GL_ARRAY_BUFFER, m_VBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(float) * m_vcount * 3, m_vertices->data(), GL_STATIC_DRAW);
    // vs 的第 0 个属性必须是 position
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);

    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_EBO);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(unsigned int) * m_icount, m_indices->data(), GL_STATIC_DRAW);

    glBindBuffer(GL_ARRAY_BUFFER, m_uvBuffer);
    glBufferData(GL_ARRAY_BUFFER, sizeof(float) * m_vcount * 2, m_uv->data(), GL_STATIC_DRAW);
    //vs 的第 1 个属性必须是 uv 坐标
    glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 2 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(1);

    glBindBuffer(GL_ARRAY_BUFFER, m_normBuffer);
    glBufferData(GL_ARRAY_BUFFER, sizeof(float) * m_vcount * 3, m_normals->data(), GL_STATIC_DRAW);
    //vs 的第 2 个属性必须是法线 normal
    glVertexAttribPointer(2, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(2);

    glBindBuffer(GL_ARRAY_BUFFER, 0);
    glBindVertexArray(0);

}

void Mesh::SendToGPU() {

    glBindVertexArray(m_VAO);
    
    Window::Instance()->SetIndexCount(m_icount);
}

std::shared_ptr<Mesh> Mesh::cube = nullptr;

std::shared_ptr<Mesh> Mesh::GetCube() {
    if (cube != nullptr) return cube;

    verticesPtr vp = std::make_shared<std::vector<float>>(std::vector<float>({
       -0.5f, -0.5f, -0.5f,
    0.5f, -0.5f, -0.5f,
    0.5f,  0.5f, -0.5f,
    0.5f,  0.5f, -0.5f,
   -0.5f,  0.5f, -0.5f,
   -0.5f, -0.5f, -0.5f,

   -0.5f, -0.5f,  0.5f,
    0.5f, -0.5f,  0.5f,
    0.5f,  0.5f,  0.5f,
    0.5f,  0.5f,  0.5f,
   -0.5f,  0.5f,  0.5f,
   -0.5f, -0.5f,  0.5f,

   -0.5f,  0.5f,  0.5f,
   -0.5f,  0.5f, -0.5f,
   -0.5f, -0.5f, -0.5f,
   -0.5f, -0.5f, -0.5f,
   -0.5f, -0.5f,  0.5f,
   -0.5f,  0.5f,  0.5f,

    0.5f,  0.5f,  0.5f,
    0.5f,  0.5f, -0.5f,
    0.5f, -0.5f, -0.5f,
    0.5f, -0.5f, -0.5f,
    0.5f, -0.5f,  0.5f,
    0.5f,  0.5f,  0.5f,

   -0.5f, -0.5f, -0.5f,
    0.5f, -0.5f, -0.5f,
    0.5f, -0.5f,  0.5f,
    0.5f, -0.5f,  0.5f,
   -0.5f, -0.5f,  0.5f,
   -0.5f, -0.5f, -0.5f,

   -0.5f,  0.5f, -0.5f,
    0.5f,  0.5f, -0.5f,
    0.5f,  0.5f,  0.5f,
    0.5f,  0.5f,  0.5f,
   -0.5f,  0.5f,  0.5f,
   -0.5f,  0.5f, -0.5f,
        }));

    indicesPtr ip = std::make_shared<std::vector<unsigned int>>(std::vector<unsigned int>({
        0, 1, 2,
        3, 4, 5,
        6, 7, 8,
        9, 10, 11,
        12, 13, 14,
        15, 16, 17,
        18, 19, 20,
        21, 22, 23,
        24, 25, 26,
        27, 28, 29,
        30, 31, 32,
        33, 34, 35
        }));

    uvPtr uvp = std::make_shared<std::vector<float>>(std::vector<float>({
        0.0f, 0.0f,
        1.0f, 0.0f,
        1.0f, 1.0f,
        1.0f, 1.0f,
        0.0f, 1.0f,
        0.0f, 0.0f,

        0.0f, 0.0f,
        1.0f, 0.0f,
        1.0f, 1.0f,
        1.0f, 1.0f,
        0.0f, 1.0f,
        0.0f, 0.0f,

        1.0f, 0.0f,
        1.0f, 1.0f,
        0.0f, 1.0f,
        0.0f, 1.0f,
        0.0f, 0.0f,
        1.0f, 0.0f,

        1.0f, 0.0f,
        1.0f, 1.0f,
        0.0f, 1.0f,
        0.0f, 1.0f,
        0.0f, 0.0f,
        1.0f, 0.0f,

        0.0f, 1.0f,
        1.0f, 1.0f,
        1.0f, 0.0f,
        1.0f, 0.0f,
        0.0f, 0.0f,
        0.0f, 1.0f,

        0.0f, 1.0f,
        1.0f, 1.0f,
        1.0f, 0.0f,
        1.0f, 0.0f,
        0.0f, 0.0f,
        0.0f, 1.0f
        }));

    normalPtr np = std::make_shared<std::vector<float>>(std::vector<float>({
        0.0f,  0.0f, -1.0f,
        0.0f,  0.0f, -1.0f,
        0.0f,  0.0f, -1.0f,
        0.0f,  0.0f, -1.0f,
        0.0f,  0.0f, -1.0f,
        0.0f,  0.0f, -1.0f,

        0.0f,  0.0f, 1.0f,
        0.0f,  0.0f, 1.0f,
        0.0f,  0.0f, 1.0f,
        0.0f,  0.0f, 1.0f,
        0.0f,  0.0f, 1.0f,
        0.0f,  0.0f, 1.0f,

        -1.0f,  0.0f,  0.0f,
        -1.0f,  0.0f,  0.0f,
        -1.0f,  0.0f,  0.0f,
        -1.0f,  0.0f,  0.0f,
        -1.0f,  0.0f,  0.0f,
        -1.0f,  0.0f,  0.0f,

        1.0f,  0.0f,  0.0f,
        1.0f,  0.0f,  0.0f,
        1.0f,  0.0f,  0.0f,
        1.0f,  0.0f,  0.0f,
        1.0f,  0.0f,  0.0f,
        1.0f,  0.0f,  0.0f,

        0.0f, -1.0f,  0.0f,
        0.0f, -1.0f,  0.0f,
        0.0f, -1.0f,  0.0f,
        0.0f, -1.0f,  0.0f,
        0.0f, -1.0f,  0.0f,
        0.0f, -1.0f,  0.0f,

        0.0f,  1.0f,  0.0f,
        0.0f,  1.0f,  0.0f,
        0.0f,  1.0f,  0.0f,
        0.0f,  1.0f,  0.0f,
        0.0f,  1.0f,  0.0f,
        0.0f,  1.0f,  0.0f
        }));

    cube = std::make_shared<Mesh>(vp, ip, uvp, np);
    return cube;
}

std::shared_ptr<Mesh> Mesh::plane = nullptr;

std::shared_ptr<Mesh> Mesh::GetPlane() {
    if (plane != nullptr) return plane;

    verticesPtr vp = std::make_shared<std::vector<float>>(std::vector<float>({
        -1,  1,  0,
        -1, -1, 0,
         1, -1,  0,
         1,  1,  0
        }));

    indicesPtr ip = std::make_shared<std::vector<unsigned int>>(std::vector<unsigned int>({
        0, 1, 2,
        0, 2, 3
        }));

    uvPtr uvp = std::make_shared<std::vector<float>>(std::vector<float>({
        0, 1,
        0, 0,
        1, 0,
        1, 1
        }));

    normalPtr np = std::make_shared<std::vector<float>>(std::vector<float>({
        0, 0, 1,
        0, 0, 1,
        0, 0, 1,
        0, 0, 1
        }));

    plane = std::make_shared<Mesh>(vp, ip, uvp, np);

    return plane;
}