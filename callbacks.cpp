#include "callbacks.h"
#include "constants.h"
#include "GLFW/glfw3.h"


void callbacks::keyboard(GLFWwindow* window, int key, int scanCode, int action, int mods)
{
    if (key == GLFW_KEY_ESCAPE)
    {
        glfwDestroyWindow(window);
    }
}
