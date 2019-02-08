#pragma once

#include <map>
#include <string>

#include "glm.hpp"
#include "gtc/quaternion.hpp"
#include "PxPhysicsAPI.h"


/* Interface for interacting with the physics engine (PhysX) */
class PhysicsEngine
{
public:
    /**
     * Initializes the physics engine. Debugging can be toggled on or off.
     * @param enableDebugging - Toggles debugging of the physics engine
     */
    explicit PhysicsEngine(bool enableDebugging = false);
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
     * Get the absolute position of the rigid body matching the given ID
     * @param id - Rigid body's unique ID
     * @return Absolute position as a Vec3
     */
    glm::vec3 getRigidBodyPosition(int id) const;

    /**
     * Get the rotation of the rigid body matching the given ID
     * @param id - Rigid body's unique ID
     * @param angleInDegrees - OUT - Rotation angle in degrees
     * @param rotationAxis - OUT - Rotation axis around which the rotation amount is applied
     */
    void getRigidBodyRotation(int id, float &angleInDegrees, glm::vec3 &rotationAxis);

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

    /**
     * Steps the physics simulation at the given interval
     * @param elapsedTime - Amount of seconds to advance the physics simulation
     */
    void stepPhysics(float elapsedTime);

private:
    const float GRAVITY = -9.81f;
    const float CUBE_DENSITY = 0.1f;

    physx::PxDefaultAllocator pxAllocator;
    physx::PxDefaultErrorCallback pxErrorCallback;

    physx::PxPhysics* pxPhysics = nullptr;
    physx::PxFoundation* pxFoundation = nullptr;
    physx::PxDefaultCpuDispatcher* pxDispatcher = nullptr;

    const std::string VISUAL_DEBUG_HOST = "127.0.0.1";
    const int VISUAL_DEBUG_PORT = 5425;
    const unsigned int VISUAL_DEBUG_TIMEOUT = 10;

    bool isDebugging = false;
    physx::PxPvd* pxVisualDebugger = nullptr;
    physx::PxPvdTransport* pxVisualDebugTransport = nullptr;

    physx::PxScene* pxScene = nullptr;
    physx::PxMaterial* pxMaterial = nullptr;

    std::map<int, physx::PxRigidDynamic*> dynamicRigidBodies;

    /* Checks if the physics engine has been properly initialized */
    bool hasInitialized() const;

    /**
     * Get the transform of the rigid body matching the given ID
     * @param id - Rigid body's unique ID
     * @return Rigid body's transform or identity transform if not found
     */
    physx::PxTransform getRigidBodyTransform(int id) const;
};
