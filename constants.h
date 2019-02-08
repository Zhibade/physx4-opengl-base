/*
 * Application constants
 */

#pragma once


#include <string>


namespace CONSTANTS
{
    const std::string DEBUG_FLAG = "--debug";

    namespace WINDOW
    {
        constexpr int WIN_WIDTH = 1024;
        constexpr int WIN_HEIGHT = 768;
    }

    namespace RENDERING
    {
        const std::string VERT_SHADER_PATH = R"(C:\Users\Jose\Documents\TestProjects\PhysX4\shaders\simple.vert)";
        const std::string FRAG_SHADER_PATH = R"(C:\Users\Jose\Documents\TestProjects\PhysX4\shaders\diffuse.frag)";

        constexpr float BG_COLOR_R = 0.202f;
        constexpr float BG_COLOR_G = 0.193f;
        constexpr float BG_COLOR_B = 0.175f;
    }
}