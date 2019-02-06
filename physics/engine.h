#ifndef PHYSX4_PHYSICSENGINE_H
#define PHYSX4_PHYSICSENGINE_H

#include "PxPhysicsAPI.h"


/* Interface for using PhysX 4 */
class PhysicsEngine
{
public:
    PhysicsEngine();
    virtual ~PhysicsEngine();

    /* Create and add an actor to the current PhysX scene */
    void addGroundPlane();

    /* Create and initialize a PhysX scene */
    void createScene();

private:
    const float GRAVITY = -9.81f;

    physx::PxDefaultAllocator pxAllocator;
    physx::PxDefaultErrorCallback pxErrorCallback;

    physx::PxPhysics* pxPhysics = nullptr;
    physx::PxFoundation* pxFoundation = nullptr;
    physx::PxCpuDispatcher* pxDispatcher = nullptr;

    physx::PxScene* pxScene = nullptr;
    physx::PxMaterial* pxMaterial = nullptr;

    /* Checks if PhysX has been properly initialized */
    bool hasInitialized() const;
};


#endif //PHYSX4_PHYSICSENGINE_H
