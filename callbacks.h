/*
 * Callbacks for GLUT functions
 */

#ifndef PHYSX4_CALLBACKS_H
#define PHYSX4_CALLBACKS_H

struct GLFWwindow;

namespace callbacks
{
    /* Keyboard callback for GLFW (only ESC is used for closing the window) */
    void keyboard(GLFWwindow* window, int key, int scanCode, int action, int mods);
}

#endif //PHYSX4_CALLBACKS_H