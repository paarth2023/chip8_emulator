#pragma once

#include <GLFW/glfw3.h>

class keyboard {
public:
	static void keyCallback(GLFWwindow* window, int key, int scancode, int action, int mods);
};