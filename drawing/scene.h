#pragma once

#include <memory>

#include "glm.hpp"


class Cube3D;
class PhysicsEngine;
class Plane3D;
class ShaderSet;


/* 3D Scene (rendering and physics) that can contain 3D objects */
class Scene
{
public:
    /**
     * Creates a new scene. Physics are enabled by default.
     * @param enablePhysics - Toggle for using physics
     * @param debugPhysics - Toggle debugging of physics
     */
    explicit Scene(bool enablePhysics = true, bool debugPhysics = false);
    virtual ~Scene();

    /* Scene rendering loop */
    void render();

    /**
     * Sets the shader set to use when rendering
     * @param shaderSet - ShaderSet to use
     */
    void setActiveShaderSet(std::shared_ptr<ShaderSet> &shaderSet);

    /**
     * Sets the global light position of the scene
     * @param newPos - New global position of the light
     */
    void setLightPos(glm::vec3 newPos);

private:
    glm::mat4 viewMatrix = glm::mat4(1.0f);
    glm::mat4 projMatrix = glm::mat4(1.0f);

    glm::vec3 lightPos = glm::vec3(1.0f);

    std::unique_ptr<Plane3D> grid;
    std::unique_ptr<Cube3D> theCube;
    std::shared_ptr<ShaderSet> activeShaderSet;

    bool usePhysics = true;
    std::shared_ptr<PhysicsEngine> physicsEngine;
};