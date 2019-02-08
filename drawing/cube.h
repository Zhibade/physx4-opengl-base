#pragma once

#include <memory>

#include "drawable3D.h"
#include "glm.hpp"


class PhysicsEngine;


/* 3D cube rendering */
class Cube3D : public Drawable3D
{
public:
    /**
     * Creates a 3D cube with a specific ID. Physics will be enabled if a PhysicsEngine shared_ptr is given
     * @param id - Unique ID for this 3D object
     * @param physEngine - Physics engine instance pointer
     */
    Cube3D(unsigned int id, std::shared_ptr<PhysicsEngine> physEngine);
    ~Cube3D() override;

    /**
     * Draws the cube into the scene. Passes model matrix to given shader set
     * @param shaderSet - Shader set onto which to apply the model matrix
     * @param renderWireframe - Render wireframe instead of solid
     */
    void draw(std::shared_ptr<ShaderSet> &shaderSet, bool renderWireframe) override;

    /**
     * Gets the vertex and normal data for a cube with hard edges
     * @param vertexData - OUT - Vertex and normal data
     * @param size - OUT - Vertex data size
     * @param vertexCount - OUT - Number of vertex in this mesh
     */
    void getVertexData(float* &vertexData, unsigned int &size, unsigned int &vertexCount) override;

    /**
     * Initialize dynamic physics box primitive
     * @param id - Unique ID for this rigid body (so it can be retrieved by the Physics engine)
     */
    void initRigidBody(int id);

    /**
     * Resets the cube's position and rotation
     *
     * NOTE: When using physics avoid resetting transform if it will overlap with another object
     */
    void resetTransform() override;

    /**
     * Sets the absolute position of the cube in the scene
     * @param newPos - New absolute position
     *
     * NOTE: When using physics avoid moving it into other rigid bodies
     */
    void setPosition(glm::vec3 newPos) override;

    /**
     * Sets the rotation of the cube in degrees
     * @param newDegrees - Rotation in angles
     * @param newRotationAxis - Rotation axis around which the rotation is applied
     */
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

    /* Updates the absolute position and rotation from the physics simulation */
    void updateTransformFromPhysics();
};
