#pragma once

#include <memory>

#include "glm.hpp"


class ShaderSet;


class Drawable3D
{
public:
    /**
     * Draws the 3D object into the scene. Passes model matrix to given shader set
     * @param shaderSet - Shader set onto which to apply the model matrix
     * @param renderWireframe - Render wireframe instead of solid
     */
    virtual void draw(std::shared_ptr<ShaderSet> &shaderSet, bool renderWireframe);

    /**
     * Gets the vertex and normal data for this 3D object
     * @param vertexData - OUT - Vertex and normal data
     * @param size - OUT - Vertex data size
     * @param vertexCount - OUT - Number of vertex in this mesh
     */
    virtual void getVertexData(float* &vertexData, unsigned int &size, unsigned int &vertexCount) = 0;

    /* Resets position and rotation if this 3D object */
    virtual void resetTransform();

    /**
     * Sets this drawable's color
     * @param newColor - Color as RGBA to assign to this 3D object
     */
    virtual void setColor(glm::vec4 newColor);

    /**
     * Sets the absolute position of the object in the scene
     * @param newPos - New absolute position of this 3D object
     */
    virtual void setPosition(glm::vec3 newPos);

    /**
     * Sets the rotation of the object in degrees
     * @param newDegrees - New rotation in angles
     * @param newRotationAxis - Axis around which to apply the rotation
     */
    virtual void setRotation(float newDegrees, glm::vec3 newRotationAxis);

    /**
     * Sets the scale of the object
     * @param newScale - New scale value to apply to this 3D object
     */
    virtual void setScale(glm::vec3 newScale);

protected:
    explicit Drawable3D(unsigned int id);
    virtual ~Drawable3D();

    glm::vec3 position = glm::vec3(0.0f);
    float rotationDegrees = 0.f;
    glm::vec3 rotationAxis = glm::vec3(0.0f, 1.0f, 0.0f);
    glm::vec3 scale = glm::vec3(1.0f);

    glm::vec4 color = glm::vec4(0.2f, 0.5f, 0.11f, 1.f);

    /**
     * Initializes vertex buffers and prepares them for rendering
     * @param vertexData - Array containing vertex positions and normals
     * @param size - Size of the vertex data array
     * @param vertexCount - Total number of vertex for this mesh
     */
    virtual void initVertexBuffers(float* vertexData, unsigned int size, unsigned int vertexCount);

private:
    unsigned int vertCount;
    unsigned int VBO, VAO;

    glm::mat4 modelMatrix = glm::mat4(1.0f);
};
