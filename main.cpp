/*
 * This is a small application for testing PhysX 4
 */

#include <iostream>

#include "callbacks.h"
#include "constants.h"
#include "drawing/scene.h"

#include "glad/glad.h"
#include "GLFW/glfw3.h"

#include "PxPhysicsAPI.h"

#include "physics/PhysicsErrorCallback.h"

#include "utils/fileLoader.h"
#include "utils/shaderLoader.h"


physx::PxPhysics* pxPhysics = nullptr;
physx::PxFoundation* pxFoundation = nullptr;
physx::PxDefaultAllocator pxAllocator;
PhysicsErrorCallback pxErrorCallback;

/* PhysX */
bool initPhysX()
{
    pxFoundation = PxCreateFoundation(PX_PHYSICS_VERSION, pxAllocator, pxErrorCallback);
    pxPhysics = PxCreatePhysics(PX_PHYSICS_VERSION, *pxFoundation, physx::PxTolerancesScale(), true, nullptr);

    if (!pxFoundation || !pxPhysics)
    {
        std::cerr << "[ERROR] [PHYSX] :: An error occurred while initializing PhysX";
        return false;
    }

    return true;
}

/* Clean PhysX */
void cleanPhysX()
{
    pxPhysics->release();
    pxFoundation->release();
}

/* MAIN */
int main(int argc, char** argv)
{
    // Window initialization
    GLFWwindow* window;

    if (!glfwInit()) // Init GLFW
    {
        std::cerr << "[ERROR] [GLFW] :: An error occurred while initializing GLFW";
        return -1;
    }

    window = glfwCreateWindow(WIN_WIDTH, WIN_HEIGHT, "PhysX4 Test", nullptr, nullptr);
    if (!window)
    {
        glfwTerminate();
        return -1;
    }

    glfwMakeContextCurrent(window);
    glfwSetKeyCallback(window, callbacks::keyboard);

    if (!gladLoadGLLoader((GLADloadproc) glfwGetProcAddress)) // Init GLAD
    {
        return -1;
    }

    // Shaders and shapes initialization
    std::string vertShader = fileLoader::readTextFile(VERT_SHADER_PATH.c_str());
    std::string fragShader = fileLoader::readTextFile(FRAG_SHADER_PATH.c_str());

    ShaderSet simpleShaderSet(vertShader.c_str(), fragShader.c_str());
    simpleShaderSet.use();

    // Init scene
    Scene scene;
    scene.setLightPos(glm::vec3(-3.f, 3.f, 10.f));

    // Init PhysX 4
    if (!initPhysX())
    {
        return -1;
    }

    // Main loop
    while (!glfwWindowShouldClose(window))
    {
        glfwPollEvents();
        scene.render(simpleShaderSet);

        glfwSwapBuffers(window);
    }

    cleanPhysX();

    // End
    glfwTerminate();
    return 0;
}