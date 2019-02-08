/*
 * Callbacks for GLFW
 */

#pragma once


struct GLFWwindow;


namespace callbacks
{
    /* Keyboard callback for GLFW (only ESC is used for closing the window) */
    void keyboard(GLFWwindow* window, int key, int scanCode, int action, int mods);
}