#ifndef PHYSX4_SHADERLOADER_H
#define PHYSX4_SHADERLOADER_H

#include <string>
#include "glm.hpp"

class ShaderSet
{
public:
    ShaderSet(const char* vertShader, const char* fragShader);

    /* Loads passed vertex and fragment shaders and creates the shader program if successful*/
    void loadShaders(const char* vertShaderContents, const char* fragShaderContents);

    /* Sets a 4x4 Matrix property on the current shaders */
    void setMat4(const std::string &name, const glm::mat4 &mat);

    /* Sets a Vec3 property on the current shaders */
    void setVec3(const std::string &name, const glm::vec3 &vec);

    /* Sets a Vec4 property on the current shaders */
    void setVec4(const std::string &name, const glm::vec4 &vec);

    /* Use this ShaderSet for rendering */
    void use();

private:
    unsigned int ID;
};

#endif //PHYSX4_SHADERLOADER_H
