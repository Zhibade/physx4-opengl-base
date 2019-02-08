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
#include "utils/fileLoader.h"
#include "utils/shaderLoader.h"


GLFWwindow* window;
std::shared_ptr<Scene> worldScene;


/* Window initialization */
bool initWindow()
{
    if (!glfwInit())
    {
        std::cerr << "[ERROR] [GLFW] :: An error occurred while initializing GLFW";
        return false;
    }

    window = glfwCreateWindow(CONSTANTS::WINDOW::WIN_WIDTH, CONSTANTS::WINDOW::WIN_HEIGHT, "PhysX4 Test", nullptr, nullptr);
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

/* 3D world initialization*/
void initWorld()
{
    // Shaders initialization
    std::string vertShader = fileLoader::readTextFile(CONSTANTS::RENDERING::VERT_SHADER_PATH.c_str());
    std::string fragShader = fileLoader::readTextFile(CONSTANTS::RENDERING::FRAG_SHADER_PATH.c_str());

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

    initWorld();

    // Main loop
    while (!glfwWindowShouldClose(window))
    {
        update();
    }

    // Clean up
    worldScene.reset();
    glfwTerminate();

    return 0;
}