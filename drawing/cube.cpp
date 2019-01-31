#include "cube.h"
#include "glad/glad.h"
#include "GLFW/glfw3.h"
#include "glm.hpp"
#include "gtc/matrix_transform.hpp"
#include "../utils/shaderLoader.h"


Cube3D::Cube3D()
{
    float* vertexData = nullptr;
    unsigned int size = 0;
    unsigned int vertexCount = 0;

    getVertexData(vertexData, size, vertexCount);
    initVertexBuffers(vertexData, size, vertexCount);
    setRotation(-45.f, glm::vec3(0.0f, 1.0f, 0.0f));
}

void Cube3D::getVertexData(float* &vertexData, unsigned int &size, unsigned int &vertexCount)
{
    size = sizeof(CUBE_VERTEX_DATA);
    vertexData = new float[size];
    vertexCount = (size / 2) / 3; // Divide by 2 to remove normal vectors, then by 3 since each vertex is a vec3

    for (int i = 0; i < (int)size; i++)
    {
        vertexData[i] = CUBE_VERTEX_DATA[i];
    }
}