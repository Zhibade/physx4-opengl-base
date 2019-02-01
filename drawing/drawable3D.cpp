#include "drawable3D.h"
#include "glad/glad.h"
#include "GLFW/glfw3.h"
#include "glm.hpp"
#include "gtc/matrix_transform.hpp"
#include "../utils/shaderLoader.h"


void Drawable3D::draw(std::shared_ptr<ShaderSet> &shaderSet)
{
    shaderSet->setMat4("model", modelMatrix);
    shaderSet->setVec4("color", glm::vec4(0.2f, 0.5f, 0.11f, 1.f));

    glDrawArrays(GL_TRIANGLES, 0, vertCount);
    //glDrawElements(GL_TRIANGLES, sizeof(CUBE_INDEXES), GL_UNSIGNED_SHORT, nullptr);
}

void Drawable3D::resetTransform()
{
    modelMatrix = glm::mat4(1.f);

    position = glm::vec3(0.f);
    rotationDegrees = 0.f;
    rotationAxis = glm::vec3(0.f);
}

void Drawable3D::setPosition(glm::vec3 newPos)
{
    resetTransform();

    modelMatrix = glm::rotate(modelMatrix, glm::radians(rotationDegrees), rotationAxis); // Need to re-apply previous rotation
    modelMatrix = glm::translate(modelMatrix, newPos);

    position = newPos;
}

void Drawable3D::setRotation(float newDegrees, glm::vec3 newRotationAxis)
{
    resetTransform();

    modelMatrix = glm::rotate(modelMatrix, glm::radians(newDegrees), newRotationAxis);
    modelMatrix = glm::translate(modelMatrix, position); // Need to re-apply previous translation

    rotationDegrees = newDegrees;
    rotationAxis = newRotationAxis;
}

Drawable3D::~Drawable3D()
{
    glDeleteVertexArrays(1, &VAO);
    glDeleteBuffers(1, &VBO);
    //glDeleteBuffers(1, &EBO);
}

void Drawable3D::initVertexBuffers(float* vertexData, unsigned int size, unsigned int vertexCount)
{
    // Create buffers
    glGenVertexArrays(1, &VAO);
    glGenBuffers(1, &VBO);
    //glGenBuffers(1, &EBO);

    vertCount = vertexCount;

    glBindVertexArray(VAO);
    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, size, &vertexData[0], GL_DYNAMIC_DRAW); // Change to GL_STATIC_DRAW if it doesn't move

    /* Element buffer is not needed with the hard edges since every vertex is split
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO); // Bind buffer to a specific type
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(CUBE_INDEXES), CUBE_INDEXES, GL_STATIC_DRAW);*/

    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), nullptr); // Passing vertex position to shader (stride needs to be 6 to account for normals)
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)(3 * sizeof(float))); // Normals
    glEnableVertexAttribArray(0);
    glEnableVertexAttribArray(1);

    delete[] vertexData;
}