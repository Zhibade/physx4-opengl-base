#pragma once

#include <string>

#include "glm.hpp"


class ShaderSet
{
public:
    /**
     * Create a new shader set using the given vertex and fragment shaders
     * @param vertShader - Vertex shader as text (contents of the .vert file)
     * @param fragShader - Fragment shader as text (contents of the .frag file)
     */
    ShaderSet(const char* vertShader, const char* fragShader);

    /**
     * Loads given vertex and fragment shaders, and creates the shader program if successful
     * @param vertShaderContents - Vertex shader as text (contents of the .vert file)
     * @param fragShaderContents - Fragment shader as text (contents of the .frag file)
     */
    void loadShaders(const char* vertShaderContents, const char* fragShaderContents);

    /**
     * Sets a 4x4 Matrix property on the current shaders
     * @param name - Name of the property to modify
     * @param mat - 4x4 matrix value to assign
     */
    void setMat4(const std::string &name, const glm::mat4 &mat);

    /**
     * Sets a 3D vector property on the current shaders
     * @param name - Name of the property to modify
     * @param vec - Vec3 value to assign
     */
    void setVec3(const std::string &name, const glm::vec3 &vec);

    /**
     * Sets a 4D vector property on the current shaders
     * @param name - Name of the property to modify
     * @param vec - Vec4 value to assign
     */
    void setVec4(const std::string &name, const glm::vec4 &vec);

    /* Use this ShaderSet for rendering */
    void use();

private:
    unsigned int ID;
};
