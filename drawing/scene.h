#ifndef PHYSX4_DISPLAY_H
#define PHYSX4_DISPLAY_H

#include <memory>
#include "glm.hpp"


class Cube3D;
class PhysicsEngine;
class Plane3D;
class ShaderSet;


class Scene
{
public:
    explicit Scene(bool enablePhysics = true);
    virtual ~Scene();

    /* Scene rendering logic */
    void render();

    /* Sets the current light position */
    void setActiveShaderSet(std::shared_ptr<ShaderSet> &shaderSet);

    /* Sets the current light position */
    void setLightPos(glm::vec3 newPos);

private:
    glm::mat4 viewMatrix = glm::mat4(1.0f);
    glm::mat4 projMatrix = glm::mat4(1.0f);

    glm::vec3 lightPos = glm::vec3(1.0f);

    std::unique_ptr<Cube3D> theCube;
    std::unique_ptr<Plane3D> grid;
    std::shared_ptr<ShaderSet> activeShaderSet;

    bool usePhysics = true;
    std::unique_ptr<PhysicsEngine> physicsEngine;
};

#endif //PHYSX4_DISPLAY_H
