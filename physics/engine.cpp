#include <iostream>
#include "engine.h"

PhysicsEngine::PhysicsEngine()
{
    pxFoundation = PxCreateFoundation(PX_PHYSICS_VERSION, pxAllocator, pxErrorCallback);
    pxPhysics = PxCreatePhysics(PX_PHYSICS_VERSION, *pxFoundation, physx::PxTolerancesScale());

    if (!pxFoundation || !pxPhysics)
    {
        std::cerr << "[ERROR] [PHYSX] :: An error occurred while initializing PhysX";
    }

    pxDispatcher = physx::PxDefaultCpuDispatcherCreate(4);

    createScene();
}

PhysicsEngine::~PhysicsEngine()
{
    if (!hasInitialized()) return;

    pxScene->release();
    pxPhysics->release();
    pxFoundation->release();
}

void PhysicsEngine::addGroundPlane()
{
    physx::PxRigidStatic* groundPlane = physx::PxCreatePlane(*pxPhysics, physx::PxPlane(0,1,0,0), *pxMaterial);
    pxScene->addActor(*groundPlane);
}

void PhysicsEngine::createScene()
{
    if (!hasInitialized()) return;

    physx::PxSceneDesc sceneDesc(pxPhysics->getTolerancesScale());
    sceneDesc.cpuDispatcher = pxDispatcher;
    sceneDesc.gravity = physx::PxVec3(0.0f, GRAVITY, 0.0f);
    sceneDesc.filterShader	= physx::PxDefaultSimulationFilterShader;

    pxScene = pxPhysics->createScene(sceneDesc);
    pxMaterial = pxPhysics->createMaterial(0.5f, 0.5f, 0.6f);
}

bool PhysicsEngine::hasInitialized() const
{
    return !(!pxFoundation || !pxPhysics);
}
