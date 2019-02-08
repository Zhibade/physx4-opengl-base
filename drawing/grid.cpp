#include "grid.h"

#include "../physics/engine.h"

Plane3D::Plane3D(unsigned int id, std::shared_ptr<PhysicsEngine> physEngine) : Drawable3D(id)
{
    float* vertexData = nullptr;
    unsigned int size = 0;
    unsigned int vertexCount = 0;

    getVertexData(vertexData, size, vertexCount);
    initVertexBuffers(vertexData, size, vertexCount);

    physicsEngine = physEngine;

    if (physicsEngine)
    {
        initRigidBody();
    }
}

Plane3D::~Plane3D()
{
    physicsEngine.reset();
}

void Plane3D::getVertexData(float* &vertexData, unsigned int &size, unsigned int &vertexCount)
{
    size = sizeof(PLANE_VERTEX_DATA);
    vertexData = new float[size];
    vertexCount = (size / 2) / 3; // Divide by 2 to remove normal vectors, then by 3 since each vertex is a vec3

    for (int i = 0; i < (int)size; i++)
    {
        vertexData[i] = PLANE_VERTEX_DATA[i];
    }
}

void Plane3D::initRigidBody()
{
    physicsEngine->addGroundPlane(PLANE_NORMAL, position[1]);
}