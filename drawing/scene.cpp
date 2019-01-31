#include "scene.h"
#include <memory>
#include "cube.h"
#include "GLFW/glfw3.h"
#include "glm.hpp"
#include "gtc/matrix_transform.hpp"
#include "../constants.h"
#include "../utils/shaderLoader.h"


Scene::Scene()
{
    theCube = std::make_shared<Cube3D>();

    // Matrices
    viewMatrix = glm::translate(viewMatrix, glm::vec3(0.0f, -1.0f, -6.5f)); // Moving camera backwards a bit
    projMatrix = glm::perspective(glm::radians(45.f), (float)WIN_WIDTH / (float)WIN_HEIGHT, 0.1f, 100.f);
}

void Scene::render(ShaderSet &shaderSet)
{
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glClearColor(BG_COLOR_R, BG_COLOR_G, BG_COLOR_B, 1.0f);
    glClearDepth(1.0f);

    glEnable(GL_DEPTH_TEST);
    glDepthFunc(GL_LESS);

    shaderSet.setMat4("view", viewMatrix);
    shaderSet.setMat4("projection", projMatrix);

    shaderSet.setVec3("mainLight", lightPos);

    //glColor3f(0.8f, 0.0f, 0.0f);

    glViewport(0, 0, (GLsizei)WIN_WIDTH, (GLsizei)WIN_HEIGHT);
    glPushMatrix(); // BEGIN drawing

    theCube->draw(shaderSet);

    glPopMatrix(); // END drawing
}

void Scene::setLightPos(glm::vec3 newPos)
{
    lightPos = newPos;
}

Scene::~Scene()
{
    theCube = nullptr;
}
