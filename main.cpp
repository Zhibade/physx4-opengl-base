/*
 * This is a small application for testing PhysX 4
 */

#include <iostream>
#include <memory>

#include "callbacks.h"
#include "constants.h"
#include "drawing/scene.h"

#include "glad/glad.h"
#include "GLFW/glfw3.h"

#include "PxPhysicsAPI.h"

#include "physics/PhysicsErrorCallback.h"

#include "utils/fileLoader.h"
#include "utils/shaderLoader.h"


GLFWwindow* window;

physx::PxPhysics* pxPhysics = nullptr;
physx::PxFoundation* pxFoundation = nullptr;

std::shared_ptr<Scene> worldScene;


/* PhysX */
bool initPhysX()
{
    physx::PxDefaultAllocator pxAllocator;
    PhysicsErrorCallback pxErrorCallback;

    pxFoundation = PxCreateFoundation(PX_PHYSICS_VERSION, pxAllocator, pxErrorCallback);
    pxPhysics = PxCreatePhysics(PX_PHYSICS_VERSION, *pxFoundation, physx::PxTolerancesScale(), true, nullptr);

    if (!pxFoundation || !pxPhysics)
    {
        std::cerr << "[ERROR] [PHYSX] :: An error occurred while initializing PhysX";
        return false;
    }

    return true;
}

void cleanPhysX()
{
    pxFoundation->release();
    pxPhysics->release();
}

/* Window */
bool initWindow()
{
    if (!glfwInit()) // Init GLFW
    {
        std::cerr << "[ERROR] [GLFW] :: An error occurred while initializing GLFW";
        return false;
    }

    window = glfwCreateWindow(WIN_WIDTH, WIN_HEIGHT, "PhysX4 Test", nullptr, nullptr);
    if (!window)
    {
        std::cerr << "[ERROR] [GLFW] :: An error occurred while creating the window";
        glfwTerminate();
        return false;
    }

    glfwMakeContextCurrent(window);
    glfwSetKeyCallback(window, callbacks::keyboard);

    if (!gladLoadGLLoader((GLADloadproc) glfwGetProcAddress)) // Init GLAD
    {
        std::cerr << "[ERROR] [GLAD] :: An error occurred while initializing GLAD";
        return false;
    }

    return true;
}

/* 3D world */
void initWorld()
{
    // Shaders and shapes initialization
    std::string vertShader = fileLoader::readTextFile(VERT_SHADER_PATH.c_str());
    std::string fragShader = fileLoader::readTextFile(FRAG_SHADER_PATH.c_str());

    std::shared_ptr<ShaderSet> simpleShaderSet(new ShaderSet(vertShader.c_str(), fragShader.c_str()));
    simpleShaderSet->use();

    // Init scene
    worldScene = std::make_shared<Scene>();
    worldScene->setActiveShaderSet(simpleShaderSet);
    worldScene->setLightPos(glm::vec3(-3.f, 3.f, 10.f));
}

/* App update per frame */
void update()
{
    glfwPollEvents();
    worldScene->render();

    glfwSwapBuffers(window);
}

/* MAIN */
int main(int argc, char** argv)
{
    if (!initWindow())
    {
        return -1;
    }

    if (!initPhysX())
    {
        return -1;
    }

    initWorld();

    // Main loop
    while (!glfwWindowShouldClose(window))
    {
        update();
    }

    // Clean up
    worldScene.reset();
    cleanPhysX();
    glfwTerminate();

    return 0;
}