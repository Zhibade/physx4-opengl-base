#ifndef PHYSX4_DRAWABLE3D_H
#define PHYSX4_DRAWABLE3D_H

#include "glm.hpp"


class ShaderSet;


class Drawable3D
{
public:
    /* Draws the cube into the scene. Passes model matrix to given shader set */
    virtual void draw(ShaderSet &shaderSet);

    /* Gets the vertex and normal data for this 3D drawable */
    virtual void getVertexData(float* &vertexData, unsigned int &size, unsigned int &vertexCount) = 0;

    /* Resets position and rotation to the default values */
    virtual void resetTransform();

    /* Sets the absolute position of the cube in the scene */
    virtual void setPosition(glm::vec3 newPos);

    /* Sets the rotation of the cube in degrees */
    virtual void setRotation(float newDegrees, glm::vec3 newRotationAxis);

protected:
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
