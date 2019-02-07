#include "scene.h"
#include <memory>
#include "cube.h"
#include "GLFW/glfw3.h"
#include "glm.hpp"
#include "gtc/matrix_transform.hpp"
#include "grid.h"
#include "../constants.h"
#include "../physics/engine.h"
#include "../utils/shaderLoader.h"


Scene::Scene(bool enablePhysics)
{
    usePhysics = enablePhysics;

    if (usePhysics)
    {
        physicsEngine = std::make_shared<PhysicsEngine>();
    }

    grid = std::make_unique<Plane3D>(1, physicsEngine);
    theCube = std::make_unique<Cube3D>(2, physicsEngine);

    grid->setColor(glm::vec4(0.7f, 0.7f, 0.7f, 1.0f));
    grid->setScale(glm::vec3(2.0f, 2.0f, 2.0f));

    theCube->setRotation(-45.f, glm::vec3(0.0f, 1.0f, 0.0f));
    theCube->setPosition(glm::vec3(0.f, 0.5f, 0.f));

    // Matrices
    viewMatrix = glm::translate(viewMatrix, glm::vec3(0.0f, -1.0f, -6.5f)); // Moving camera backwards a bit
    projMatrix = glm::perspective(glm::radians(45.f), (float)WIN_WIDTH / (float)WIN_HEIGHT, 0.1f, 100.f);
}

void Scene::render()
{
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glClearColor(BG_COLOR_R, BG_COLOR_G, BG_COLOR_B, 1.0f);
    glClearDepth(1.0f);

    glEnable(GL_DEPTH_TEST);
    glDepthFunc(GL_LESS);

    activeShaderSet->setMat4("view", viewMatrix);
    activeShaderSet->setMat4("projection", projMatrix);

    activeShaderSet->setVec3("mainLight", lightPos);

    //glColor3f(0.8f, 0.0f, 0.0f);

    glViewport(0, 0, (GLsizei)WIN_WIDTH, (GLsizei)WIN_HEIGHT);
    glPushMatrix(); // BEGIN drawing

    grid->draw(activeShaderSet, false);
    theCube->draw(activeShaderSet, false);

    glPopMatrix(); // END drawing
}

void Scene::setActiveShaderSet(std::shared_ptr<ShaderSet> &shaderSet)
{
    activeShaderSet = shaderSet;
}

void Scene::setLightPos(glm::vec3 newPos)
{
    lightPos = newPos;
}

Scene::~Scene()
{
    grid.reset();
    theCube.reset();
    activeShaderSet.reset();
    physicsEngine.reset();
}
