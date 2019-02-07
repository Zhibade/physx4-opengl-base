#ifndef PHYSX4_CUBE_H
#define PHYSX4_CUBE_H

#include <memory>
#include "drawable3D.h"
#include "glm.hpp"

class PhysicsEngine;


/* Create and manipulate a 3D cube */
class Cube3D : public Drawable3D
{
public:
    Cube3D(unsigned int id, std::shared_ptr<PhysicsEngine> physEngine);
    ~Cube3D() override;

    /* Gets the vertex and normal data for a cube with hard edges */
    void getVertexData(float* &vertexData, unsigned int &size, unsigned int &vertexCount) override;

    /* Initialize dynamic physics box primitive */
    void initRigidBody(int id);

    /* Sets the absolute position of the cube in the scene */
    void setPosition(glm::vec3 newPos) override;

    /* Sets the rotation of the cube in degrees */
    void setRotation(float newDegrees, glm::vec3 newRotationAxis) override;

private:
    const float CUBE_HALF_EXTENT = 0.5f;
    const float CUBE_VERTEX_DATA[216] = {
            // Vertex             // Normals
            -CUBE_HALF_EXTENT, -CUBE_HALF_EXTENT, -CUBE_HALF_EXTENT,  0.0f,  0.0f, -1.0f,
            CUBE_HALF_EXTENT, -CUBE_HALF_EXTENT, -CUBE_HALF_EXTENT,  0.0f,  0.0f, -1.0f,
            CUBE_HALF_EXTENT,  CUBE_HALF_EXTENT, -CUBE_HALF_EXTENT,  0.0f,  0.0f, -1.0f,
            CUBE_HALF_EXTENT,  CUBE_HALF_EXTENT, -CUBE_HALF_EXTENT,  0.0f,  0.0f, -1.0f,
            -CUBE_HALF_EXTENT,  CUBE_HALF_EXTENT, -CUBE_HALF_EXTENT,  0.0f,  0.0f, -1.0f,
            -CUBE_HALF_EXTENT, -CUBE_HALF_EXTENT, -CUBE_HALF_EXTENT,  0.0f,  0.0f, -1.0f,

            -CUBE_HALF_EXTENT, -CUBE_HALF_EXTENT,  CUBE_HALF_EXTENT,  0.0f,  0.0f,  1.0f,
            CUBE_HALF_EXTENT, -CUBE_HALF_EXTENT,  CUBE_HALF_EXTENT,  0.0f,  0.0f,  1.0f,
            CUBE_HALF_EXTENT,  CUBE_HALF_EXTENT,  CUBE_HALF_EXTENT,  0.0f,  0.0f,  1.0f,
            CUBE_HALF_EXTENT,  CUBE_HALF_EXTENT,  CUBE_HALF_EXTENT,  0.0f,  0.0f,  1.0f,
            -CUBE_HALF_EXTENT,  CUBE_HALF_EXTENT,  CUBE_HALF_EXTENT,  0.0f,  0.0f,  1.0f,
            -CUBE_HALF_EXTENT, -CUBE_HALF_EXTENT,  CUBE_HALF_EXTENT,  0.0f,  0.0f,  1.0f,

            -CUBE_HALF_EXTENT,  CUBE_HALF_EXTENT,  CUBE_HALF_EXTENT, -1.0f,  0.0f,  0.0f,
            -CUBE_HALF_EXTENT,  CUBE_HALF_EXTENT, -CUBE_HALF_EXTENT, -1.0f,  0.0f,  0.0f,
            -CUBE_HALF_EXTENT, -CUBE_HALF_EXTENT, -CUBE_HALF_EXTENT, -1.0f,  0.0f,  0.0f,
            -CUBE_HALF_EXTENT, -CUBE_HALF_EXTENT, -CUBE_HALF_EXTENT, -1.0f,  0.0f,  0.0f,
            -CUBE_HALF_EXTENT, -CUBE_HALF_EXTENT,  CUBE_HALF_EXTENT, -1.0f,  0.0f,  0.0f,
            -CUBE_HALF_EXTENT,  CUBE_HALF_EXTENT,  CUBE_HALF_EXTENT, -1.0f,  0.0f,  0.0f,

            CUBE_HALF_EXTENT,  CUBE_HALF_EXTENT,  CUBE_HALF_EXTENT,  1.0f,  0.0f,  0.0f,
            CUBE_HALF_EXTENT,  CUBE_HALF_EXTENT, -CUBE_HALF_EXTENT,  1.0f,  0.0f,  0.0f,
            CUBE_HALF_EXTENT, -CUBE_HALF_EXTENT, -CUBE_HALF_EXTENT,  1.0f,  0.0f,  0.0f,
            CUBE_HALF_EXTENT, -CUBE_HALF_EXTENT, -CUBE_HALF_EXTENT,  1.0f,  0.0f,  0.0f,
            CUBE_HALF_EXTENT, -CUBE_HALF_EXTENT,  CUBE_HALF_EXTENT,  1.0f,  0.0f,  0.0f,
            CUBE_HALF_EXTENT,  CUBE_HALF_EXTENT,  CUBE_HALF_EXTENT,  1.0f,  0.0f,  0.0f,

            -CUBE_HALF_EXTENT, -CUBE_HALF_EXTENT, -CUBE_HALF_EXTENT,  0.0f, -1.0f,  0.0f,
            CUBE_HALF_EXTENT, -CUBE_HALF_EXTENT, -CUBE_HALF_EXTENT,  0.0f, -1.0f,  0.0f,
            CUBE_HALF_EXTENT, -CUBE_HALF_EXTENT,  CUBE_HALF_EXTENT,  0.0f, -1.0f,  0.0f,
            CUBE_HALF_EXTENT, -CUBE_HALF_EXTENT,  CUBE_HALF_EXTENT,  0.0f, -1.0f,  0.0f,
            -CUBE_HALF_EXTENT, -CUBE_HALF_EXTENT,  CUBE_HALF_EXTENT,  0.0f, -1.0f,  0.0f,
            -CUBE_HALF_EXTENT, -CUBE_HALF_EXTENT, -CUBE_HALF_EXTENT,  0.0f, -1.0f,  0.0f,

            -CUBE_HALF_EXTENT,  CUBE_HALF_EXTENT, -CUBE_HALF_EXTENT,  0.0f,  1.0f,  0.0f,
            CUBE_HALF_EXTENT,  CUBE_HALF_EXTENT, -CUBE_HALF_EXTENT,  0.0f,  1.0f,  0.0f,
            CUBE_HALF_EXTENT,  CUBE_HALF_EXTENT,  CUBE_HALF_EXTENT,  0.0f,  1.0f,  0.0f,
            CUBE_HALF_EXTENT,  CUBE_HALF_EXTENT,  CUBE_HALF_EXTENT,  0.0f,  1.0f,  0.0f,
            -CUBE_HALF_EXTENT,  CUBE_HALF_EXTENT,  CUBE_HALF_EXTENT,  0.0f,  1.0f,  0.0f,
            -CUBE_HALF_EXTENT,  CUBE_HALF_EXTENT, -CUBE_HALF_EXTENT,  0.0f,  1.0f,  0.0f
    };

    int rigidBodyID;
    std::shared_ptr<PhysicsEngine> physicsEngine;
};

#endif //PHYSX4_CUBE_H
