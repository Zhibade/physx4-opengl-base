#pragma once

#include <memory>

#include "drawable3D.h"


class PhysicsEngine;

/* 3D plane rendering */
class Plane3D : public Drawable3D
{
public:
    /**
     * Creates a 3D plane with a specific ID. Physics will be enabled if a PhysicsEngine shared_ptr is given
     * @param id - Unique ID for this 3D object
     * @param physEngine - Physics engine instance pointer
     *
     * NOTE: Plane physics is currently implemented only as an infinite static plane
     */
    Plane3D(unsigned int id, std::shared_ptr<PhysicsEngine> physEngine);
    ~Plane3D() override;

    /**
     * Gets the vertex and normal data for a 3D plane
     * @param vertexData - OUT - Vertex and normal data
     * @param size - OUT - Vertex data size
     * @param vertexCount - OUT - Number of vertex in this mesh
     */
    void getVertexData(float* &vertexData, unsigned int &size, unsigned int &vertexCount) override;

    /**
     * Initialize static physics plane primitive
     * @param id - Unique ID for this rigid body (so it can be retrieved by the Physics engine)
     */
    void initRigidBody();

private:
    const glm::vec3 PLANE_NORMAL = glm::vec3(0.f, 1.f, 0.f);

    const float PLANE_VERTEX_DATA[36] = {
            // Vertex             // Normals
            -2.5f, 0.0f, -2.5f, PLANE_NORMAL[0], PLANE_NORMAL[1], PLANE_NORMAL[2],
            -2.5f, 0.0f, 2.5f, PLANE_NORMAL[0], PLANE_NORMAL[1], PLANE_NORMAL[2],
            2.5f, 0.0f, 2.5f, PLANE_NORMAL[0], PLANE_NORMAL[1], PLANE_NORMAL[2],

            2.5f, 0.0f, 2.5f, PLANE_NORMAL[0], PLANE_NORMAL[1], PLANE_NORMAL[2],
            2.5f, 0.0f, -2.5f, PLANE_NORMAL[0], PLANE_NORMAL[1], PLANE_NORMAL[2],
            -2.5f, 0.0f, -2.5f, PLANE_NORMAL[0], PLANE_NORMAL[1], PLANE_NORMAL[2]
    };

    std::shared_ptr<PhysicsEngine> physicsEngine;
};
