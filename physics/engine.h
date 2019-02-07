#ifndef PHYSX4_PHYSICSENGINE_H
#define PHYSX4_PHYSICSENGINE_H

#include <map>
#include "glm.hpp"
#include "gtc/quaternion.hpp"
#include "PxPhysicsAPI.h"


/* Abstraction interface for using PhysX 4 */
class PhysicsEngine
{
public:
    PhysicsEngine();
    virtual ~PhysicsEngine();

    /* Create and add a box rigid body to the current physics simulation */
    void addBox(int id, glm::vec3 position, float angleInDegrees, glm::vec3 rotationAxis, glm::vec3 halfExtents);

    /* Create and add an infinite static rigid body plane to the current physics simulation */
    void addGroundPlane(glm::vec3 normal, float distanceFromOrigin = 0.f);

    /* Create and initialize a PhysX scene */
    void createScene();

    /* Set dynamic rigid body's global transform */
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

    /* Checks if PhysX has been properly initialized */
    bool hasInitialized() const;
};


#endif //PHYSX4_PHYSICSENGINE_H
