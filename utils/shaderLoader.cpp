#include "shaderLoader.h"
#include <iostream>
#include "glad/glad.h"


ShaderSet::ShaderSet(const char* vertShader, const char* fragShader)
{
    loadShaders(vertShader, fragShader);
}

void ShaderSet::loadShaders(const char* vertShaderContents, const char* fragShaderContents)
{
    GLuint vertShader = glCreateShader(GL_VERTEX_SHADER);
    GLuint fragShader = glCreateShader(GL_FRAGMENT_SHADER);

    // Vert shader
    glShaderSource(vertShader, 1, &vertShaderContents, nullptr);
    glCompileShader(vertShader);

    int vertShaderSuccess;
    glGetShaderiv(vertShader, GL_COMPILE_STATUS, &vertShaderSuccess); // Check if compilation was successful
    if (!vertShaderSuccess)
    {
        char log[512];
        glGetShaderInfoLog(vertShader, 512, nullptr, log);
        std::cout << "[SHADER ERROR] :: VERTEX \n" << log << std::endl;
    }
    else
    {
        std::cout << "[SHADER] :: Loaded vertex shader." << std::endl;
    }

    // Frag shader
    glShaderSource(fragShader, 1, &fragShaderContents, nullptr);
    glCompileShader(fragShader);

    int fragShaderSuccess;
    glGetShaderiv(fragShader, GL_COMPILE_STATUS, &fragShaderSuccess); // Check if compilation was successful
    if (!fragShaderSuccess)
    {
        char log[512];
        glGetShaderInfoLog(fragShader, 512, nullptr, log);
        std::cout << "[SHADER ERROR] :: FRAGMENT \n" << log << std::endl;
    }
    else
    {
        std::cout << "[SHADER] :: Loaded fragment shader." << std::endl;
    }

    // Link shaders to program and use program
    ID = glCreateProgram();
    glAttachShader(ID, vertShader);
    glAttachShader(ID, fragShader);
    glLinkProgram(ID);

    int programSuccess;
    glGetProgramiv(ID, GL_LINK_STATUS, &programSuccess);
    if (!programSuccess)
    {
        char log[512];
        glGetProgramInfoLog(ID, 512, nullptr, log);
        std::cout << "[SHADER ERROR] :: PROGRAM LINK \n" << log << std::endl;
    }

    glDeleteShader(vertShader);
    glDeleteShader(fragShader);

    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);
}

void ShaderSet::setMat4(const std::string &name, const glm::mat4 &mat)
{
    glUniformMatrix4fv(glGetUniformLocation(ID, name.c_str()), 1, GL_FALSE, &mat[0][0]);
}

void ShaderSet::setVec3(const std::string &name, const glm::vec3 &vec)
{
    glUniform3f(glGetUniformLocation(ID, name.c_str()), vec[0], vec[1], vec[2]);
}

void ShaderSet::setVec4(const std::string &name, const glm::vec4 &vec)
{
    glUniform4f(glGetUniformLocation(ID, name.c_str()), vec[0], vec[1], vec[2], vec[3]);
}

void ShaderSet::use()
{
    glUseProgram(ID);
}