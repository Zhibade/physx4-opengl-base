#include "cube.h"
#include "glad/glad.h"
#include "GLFW/glfw3.h"
#include "glm.hpp"
#include "gtc/matrix_transform.hpp"
#include "../physics/engine.h"
#include "../utils/shaderLoader.h"


Cube3D::Cube3D(unsigned int id, std::shared_ptr<PhysicsEngine> physEngine) : Drawable3D(id)
{
    float* vertexData = nullptr;
    unsigned int size = 0;
    unsigned int vertexCount = 0;

    getVertexData(vertexData, size, vertexCount);
    initVertexBuffers(vertexData, size, vertexCount);

    physicsEngine = physEngine;

    if (physicsEngine)
    {
        initRigidBody(id);
    }
}

Cube3D::~Cube3D()
{
    physicsEngine.reset();
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

void Cube3D::initRigidBody(int id)
{
    rigidBodyID = id;
    physicsEngine->addBox(rigidBodyID, position, rotationDegrees, rotationAxis, glm::vec3(CUBE_HALF_EXTENT));
}

void Cube3D::setPosition(glm::vec3 newPos)
{
    Drawable3D::setPosition(newPos);
    physicsEngine->setRigidBodyTransform(rigidBodyID, position, rotationDegrees, rotationAxis);
}

void Cube3D::setRotation(float newDegrees, glm::vec3 newRotationAxis)
{
    Drawable3D::setRotation(newDegrees, newRotationAxis);
    physicsEngine->setRigidBodyTransform(rigidBodyID, position, rotationDegrees, rotationAxis);
}