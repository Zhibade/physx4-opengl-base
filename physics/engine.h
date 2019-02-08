#pragma once

#include <map>

#include "glm.hpp"
#include "gtc/quaternion.hpp"
#include "PxPhysicsAPI.h"


/* Interface for interacting with the physics engine (PhysX) */
class PhysicsEngine
{
public:
    PhysicsEngine();
    virtual ~PhysicsEngine();

    /**
     * Create and add a dynamic rigid body box primitive
     * @param id - Unique ID for this rigid body
     * @param position - Initial absolute position
     * @param angleInDegrees - Initial rotation amount in angles
     * @param rotationAxis - Initial rotation axis around which the rotation amount is applied
     * @param halfExtents - Half length of the box
     */
    void addBox(int id, glm::vec3 position, float angleInDegrees, glm::vec3 rotationAxis, glm::vec3 halfExtents);

    /**
     * Create and add an infinite plane as a static rigid body
     * @param normal - Normal of the plane
     * @param distanceFromOrigin - Distance from the origin of the scene
     */
    void addGroundPlane(glm::vec3 normal, float distanceFromOrigin = 0.f);

    /* Initializes a physics scene */
    void createScene();

    /**
     * Sets the transform of a specific rigid body
     * @param id - Unique ID for the target rigid body
     * @param position - New absolute position
     * @param angleInDegrees - New rotation angle in degrees
     * @param rotationAxis - New axis around which to apply the rotation
     *
     * NOTE: Avoid moving or rotating rigid bodies into other rigid bodies to avoid errors in the physics simulation
     */
    void setRigidBodyTransform(int id, glm::vec3 position, float angleInDegrees, glm::vec3 rotationAxis);

private:
    const float GRAVITY = -9.81f;
    const float CUBE_DENSITY = 10.f;

    physx::PxDefaultAllocator pxAllocator;
    physx::PxDefaultErrorCallback pxErrorCallback;

    physx::PxPhysics* pxPhysics = nullptr;
    physx::PxFoundation* pxFoundation = nullptr;
    physx::PxDefaultCpuDispatcher* pxDispatcher = nullptr;

    physx::PxScene* pxScene = nullptr;
    physx::PxMaterial* pxMaterial = nullptr;

    std::map<int, physx::PxRigidDynamic*> dynamicRigidBodies;

    /* Checks if the physics engine has been properly initialized */
    bool hasInitialized() const;
};
