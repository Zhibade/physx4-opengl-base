#include "drawable3D.h"

#include "glad/glad.h"
#include "GLFW/glfw3.h"
#include "glm.hpp"
#include "gtc/matrix_transform.hpp"
#include "../utils/shaderLoader.h"


void Drawable3D::draw(std::shared_ptr<ShaderSet> &shaderSet, bool renderWireframe)
{
    shaderSet->setMat4("model", modelMatrix);
    shaderSet->setVec4("color", color);

    auto drawMode = renderWireframe ? GL_LINE_STRIP : GL_TRIANGLES;

    glBindVertexArray(VAO); // Need to rebind vertex array on each draw so we can have multiple objects with different shapes
    glDrawArrays(drawMode, 0, vertCount);
}

void Drawable3D::resetTransform()
{
    modelMatrix = glm::mat4(1.f);

    position = glm::vec3(0.f);
    rotationDegrees = 0.f;
    rotationAxis = glm::vec3(0.0f, 1.0f, 0.0f);
}

void Drawable3D::setColor(glm::vec4 newColor)
{
    color = newColor;
}

void Drawable3D::setPosition(glm::vec3 newPos)
{
    modelMatrix = glm::mat4(1.f);

    modelMatrix = glm::rotate(modelMatrix, glm::radians(rotationDegrees), rotationAxis);
    modelMatrix = glm::scale(modelMatrix, scale);
    modelMatrix = glm::translate(modelMatrix, newPos);

    position = newPos;
}

void Drawable3D::setRotation(float newDegrees, glm::vec3 newRotationAxis)
{
    modelMatrix = glm::mat4(1.f);

    modelMatrix = glm::rotate(modelMatrix, glm::radians(newDegrees), newRotationAxis);
    modelMatrix = glm::scale(modelMatrix, scale);
    modelMatrix = glm::translate(modelMatrix, position);

    rotationDegrees = newDegrees;
    rotationAxis = newRotationAxis;
}

void Drawable3D::setScale(glm::vec3 newScale)
{
    modelMatrix = glm::mat4(1.f);

    modelMatrix = glm::rotate(modelMatrix, glm::radians(rotationDegrees), rotationAxis);
    modelMatrix = glm::scale(modelMatrix, newScale);
    modelMatrix = glm::translate(modelMatrix, position);
}

Drawable3D::Drawable3D(unsigned int id)
{
    VAO = id;
    VBO = id;
}

Drawable3D::~Drawable3D()
{
    glDeleteVertexArrays(1, &VAO);
    glDeleteBuffers(1, &VBO);
}

void Drawable3D::initVertexBuffers(float* vertexData, unsigned int size, unsigned int vertexCount)
{
    // Create buffers
    glGenVertexArrays(1, &VAO);
    glGenBuffers(1, &VBO);

    vertCount = vertexCount;

    glBindVertexArray(VAO);
    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, size, &vertexData[0], GL_DYNAMIC_DRAW); // Change to GL_STATIC_DRAW if it doesn't move

    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), nullptr); // Passing vertex position to shader (stride needs to be 6 to account for normals)
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)(3 * sizeof(float))); // Normals
    glEnableVertexAttribArray(0);
    glEnableVertexAttribArray(1);

    delete[] vertexData;
}