#ifndef PHYSX4_GRID_H
#define PHYSX4_GRID_H

#include <memory>
#include "drawable3D.h"

class PhysicsEngine;


class Plane3D : public Drawable3D
{
public:
    Plane3D(unsigned int id, std::shared_ptr<PhysicsEngine> physEngine);
    ~Plane3D() override;

    /* Gets the vertex data for the grid lines */
    void getVertexData(float* &vertexData, unsigned int &size, unsigned int &vertexCount) override;

    /* Initialize static physics plane primitive */
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


#endif //PHYSX4_GRID_H
