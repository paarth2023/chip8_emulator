#include "keyboard.h"
#include "chip8.h"

void keyboard::keyCallback(GLFWwindow* window, int key, int scanmode, int action, int mods) {
	Chip8* context = static_cast<Chip8*>(glfwGetWindowUserPointer(window));
	switch (key) {
	case GLFW_KEY_1: {
		if (action == GLFW_PRESS) std::cout << "1 was pressed\n";
		if (action == GLFW_RELEASE) std::cout << "1 was released\n";
		break;

	case GLFW_KEY_2: {
		if (action == GLFW_PRESS) std::cout << "2 was pressed\n";
		if (action == GLFW_RELEASE) std::cout << "2 was released\n";
		break;
	}

	case GLFW_KEY_3: {
		if (action == GLFW_PRESS) std::cout << "3 was pressed\n";
		if (action == GLFW_RELEASE) std::cout << "3 was released\n";
		break;
	}
	case GLFW_KEY_4: {
		if (action == GLFW_PRESS) std::cout << "C was pressed\n";
		if (action == GLFW_RELEASE) std::cout << "C was released\n";
		break;
	}

	case GLFW_KEY_Q: {
		if (action == GLFW_PRESS) std::cout << "4 was pressed\n";
		if (action == GLFW_RELEASE) std::cout << "4 was released\n";
		break;
	}

	case GLFW_KEY_W: {
		if (action == GLFW_PRESS) std::cout << "5 was pressed\n";
		if (action == GLFW_RELEASE) std::cout << "5 was released\n";
		break;
	}

	case GLFW_KEY_E: {
		if (action == GLFW_PRESS) std::cout << "6 was pressed\n";
		if (action == GLFW_RELEASE) std::cout << "6 was released\n";
		break;
	}

	case GLFW_KEY_R: {
		if (action == GLFW_PRESS) std::cout << "D was pressed\n";
		if (action == GLFW_RELEASE) std::cout << "D was released\n";
		break;
	}

	case GLFW_KEY_A: {
		if (action == GLFW_PRESS) std::cout << "7 was pressed\n";
		if (action == GLFW_RELEASE) std::cout << "7 was released\n";
		break;
	}

	case GLFW_KEY_S: {
		if (action == GLFW_PRESS) std::cout << "8 was pressed\n";
		if (action == GLFW_RELEASE) std::cout << "8 was released\n";
		break;
	}

	case GLFW_KEY_D: {
		if (action == GLFW_PRESS) std::cout << "9 was pressed\n";
		if (action == GLFW_RELEASE) std::cout << "9 was released\n";
		break;
	}

	case GLFW_KEY_F: {
		if (action == GLFW_PRESS) std::cout << "E was pressed\n";
		if (action == GLFW_RELEASE) std::cout << "E was released\n";
		break;
	}

	case GLFW_KEY_Z: {
		if (action == GLFW_PRESS) std::cout << "A was pressed\n";
		if (action == GLFW_RELEASE) std::cout << "A was released\n";
		break;
	}

	case GLFW_KEY_X: {
		if (action == GLFW_PRESS) std::cout << "0 was pressed\n";
		if (action == GLFW_RELEASE) std::cout << "0 was released\n";
		break;
	}

	case GLFW_KEY_C: {
		if (action == GLFW_PRESS) std::cout << "B was pressed\n";
		if (action == GLFW_RELEASE) std::cout << "B was released\n";
		break;
	}

	case GLFW_KEY_V: {
		if (action == GLFW_PRESS) std::cout << "F was pressed\n";
		if (action == GLFW_RELEASE) std::cout << "F was released\n";
		break;
	}
	}
	default:
		break;
	}
}