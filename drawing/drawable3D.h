#ifndef PHYSX4_DRAWABLE3D_H
#define PHYSX4_DRAWABLE3D_H

#include <memory>
#include "glm.hpp"


class ShaderSet;


class Drawable3D
{
public:
    /* Draws the drawable into the scene. Passes model matrix to given shader set */
    virtual void draw(std::shared_ptr<ShaderSet> &shaderSet, bool renderWireframe);

    /* Gets the vertex and normal data for this 3D drawable. Abstract function. */
    virtual void getVertexData(float* &vertexData, unsigned int &size, unsigned int &vertexCount) = 0;

    /* Resets position and rotation to the origin with no rotation */
    virtual void resetTransform();

    /* Sets the absolute position of the object in the scene */
    virtual void setPosition(glm::vec3 newPos);

    /* Sets the rotation of the object in degrees */
    virtual void setRotation(float newDegrees, glm::vec3 newRotationAxis);

protected:
    explicit Drawable3D(unsigned int id);
    virtual ~Drawable3D();

    /* Initializes vertex buffers and prepares them for rendering */
    virtual void initVertexBuffers(float* vertexData, unsigned int size, unsigned int vertexCount);

private:
    unsigned int vertCount;
    unsigned int VBO, VAO;

    glm::mat4 modelMatrix = glm::mat4(1.0f);
    glm::vec3 position = glm::vec3(0.0f);
    float rotationDegrees = 0.f;
    glm::vec3 rotationAxis = glm::vec3(0.0f);
};

#endif //PHYSX4_DRAWABLE3D_H
