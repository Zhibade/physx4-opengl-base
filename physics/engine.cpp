#include "engine.h"

#include <iostream>


PhysicsEngine::PhysicsEngine(bool enableDebugging)
{
    pxFoundation = PxCreateFoundation(PX_PHYSICS_VERSION, pxAllocator, pxErrorCallback);

    isDebugging = enableDebugging;
    if (isDebugging && pxFoundation)
    {
        pxVisualDebugger = physx::PxCreatePvd(*pxFoundation);
        pxVisualDebugTransport = physx::PxDefaultPvdSocketTransportCreate(VISUAL_DEBUG_HOST.c_str(),
                VISUAL_DEBUG_PORT, VISUAL_DEBUG_TIMEOUT);

        pxVisualDebugger->connect(*pxVisualDebugTransport, physx::PxPvdInstrumentationFlag::eALL);

        pxPhysics = PxCreatePhysics(PX_PHYSICS_VERSION, *pxFoundation, physx::PxTolerancesScale(), true, pxVisualDebugger);
    }
    else
    {
        pxPhysics = PxCreatePhysics(PX_PHYSICS_VERSION, *pxFoundation, physx::PxTolerancesScale());
    }

    if (!pxFoundation || !pxPhysics)
    {
        std::cerr << "[ERROR] [PHYSICS] :: An error occurred while initializing PhysX";
        return;
    }

    pxDispatcher = physx::PxDefaultCpuDispatcherCreate(4);

    createScene();
}

PhysicsEngine::~PhysicsEngine()
{
    if (!hasInitialized()) return;

    pxScene->release();
    pxDispatcher->release();
    pxPhysics->release();

    if (isDebugging)
    {
        pxVisualDebugTransport->release();
        pxVisualDebugger->release();
    }

    pxFoundation->release();
}

void PhysicsEngine::addBox(int id, glm::vec3 position, float angleInDegrees, glm::vec3 rotationAxis, glm::vec3 halfExtents)
{
    if (!hasInitialized()) return;

    physx::PxQuat rotation(glm::radians(angleInDegrees), physx::PxVec3(rotationAxis[0], rotationAxis[1], rotationAxis[2]));
    physx::PxTransform transform(position[0], position[1], position[2], rotation);

    physx::PxBoxGeometry boxGeometry(halfExtents[0], halfExtents[1], halfExtents[2]);
    physx::PxShape* shape = pxPhysics->createShape(boxGeometry, *pxMaterial);

    physx::PxRigidDynamic* rigidBody = pxPhysics->createRigidDynamic(transform);
    rigidBody->attachShape(*shape);
    physx::PxRigidBodyExt::updateMassAndInertia(*rigidBody, CUBE_DENSITY);

    pxScene->addActor(*rigidBody);
    dynamicRigidBodies.insert(std::make_pair(id, rigidBody));

    shape->release();
}

void PhysicsEngine::addGroundPlane(glm::vec3 normal, float distanceFromOrigin)
{
    if (!hasInitialized()) return;

    physx::PxPlane plane(normal[0], normal[1], normal[2], distanceFromOrigin);

    physx::PxRigidStatic* groundPlane = physx::PxCreatePlane(*pxPhysics, plane, *pxMaterial);
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

    if (isDebugging)
    {
        physx::PxPvdSceneClient* visualDebugClient = pxScene->getScenePvdClient();

        if (!visualDebugClient) return;

        visualDebugClient->setScenePvdFlag(physx::PxPvdSceneFlag::eTRANSMIT_CONSTRAINTS, true);
        visualDebugClient->setScenePvdFlag(physx::PxPvdSceneFlag::eTRANSMIT_CONTACTS, true);
        visualDebugClient->setScenePvdFlag(physx::PxPvdSceneFlag::eTRANSMIT_SCENEQUERIES, true);
    }
}

glm::vec3 PhysicsEngine::getRigidBodyPosition(int id) const
{
    physx::PxTransform transform = getRigidBodyTransform(id);
    return glm::vec3(transform.p[0], transform.p[1], transform.p[2]);
}

void PhysicsEngine::getRigidBodyRotation(int id, float &angleInDegrees, glm::vec3 &rotationAxis)
{
    physx::PxTransform transform = getRigidBodyTransform(id);

    float angleRad;
    physx::PxVec3 angleAxis;

    transform.q.toRadiansAndUnitAxis(angleRad, angleAxis);
    angleInDegrees = glm::degrees(angleRad);
    rotationAxis = glm::vec3(angleAxis.x, angleAxis.y, angleAxis.z);
}

void PhysicsEngine::setRigidBodyTransform(int id, glm::vec3 position, float angleInDegrees, glm::vec3 rotationAxis)
{
    if (!hasInitialized()) return;

    physx::PxRigidDynamic* rigidBody = dynamicRigidBodies.at(id);

    if (!rigidBody)
    {
        std::cerr << "[ERROR] [PHYSICS] :: No rigid body found with the ID: " << id << std::endl;
        return;
    }

    physx::PxQuat rotation(glm::radians(angleInDegrees), physx::PxVec3(rotationAxis[0], rotationAxis[1], rotationAxis[2]));
    physx::PxTransform transform(position[0], position[1], position[2], rotation);
    rigidBody->setGlobalPose(transform);
}

void PhysicsEngine::stepPhysics(float elapsedTime)
{
    pxScene->simulate(elapsedTime);
    pxScene->fetchResults(true);
}

bool PhysicsEngine::hasInitialized() const
{
    if (!pxFoundation || !pxPhysics)
    {
        std::cerr << "[ERROR] [PHYSICS] :: PhysX is not properly initialized. Please initialize it first before using" <<
                     " any of the physics API." << std::endl;
        return false;
    }

    return true;
}

physx::PxTransform PhysicsEngine::getRigidBodyTransform(int id) const
{
    if (!hasInitialized()) return physx::PxTransform {};

    physx::PxRigidDynamic* rigidBody = dynamicRigidBodies.at(id);

    if (!rigidBody)
    {
        std::cerr << "[ERROR] [PHYSICS] :: No rigid body found with the ID: " << id << std::endl;
        return physx::PxTransform {};
    }

    physx::PxTransform transform = rigidBody->getGlobalPose();
    return transform;
}