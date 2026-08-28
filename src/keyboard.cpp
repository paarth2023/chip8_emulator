#include "keyboard.h"
#include "chip8.h"

void keyboard::keyCallback(GLFWwindow* window, int key, int scanmode, int action, int mods) {
	Chip8* context = static_cast<Chip8*>(glfwGetWindowUserPointer(window));
	switch (key) {
	case GLFW_KEY_1: {
		if (action == GLFW_PRESS) context->handler(1, 1);
		if (action == GLFW_RELEASE) context->handler(1, 0);
		break;

	case GLFW_KEY_2: {
		if (action == GLFW_PRESS) context->handler(2, 1);

		if (action == GLFW_RELEASE) context->handler(2, 0);

		break;
	}

	case GLFW_KEY_3: {
		if (action == GLFW_PRESS) context->handler(3, 1);

		if (action == GLFW_RELEASE) context->handler(3, 0);

		break;
	}
	case GLFW_KEY_4: {
		if (action == GLFW_PRESS) context->handler(0x0C, 4);

		if (action == GLFW_RELEASE) context->handler(0x0C, 1);

		break;
	}

	case GLFW_KEY_Q: {
		if (action == GLFW_PRESS) context->handler(4, 1);

		if (action == GLFW_RELEASE) context->handler(4, 0);

		break;
	}

	case GLFW_KEY_W: {
		if (action == GLFW_PRESS) context->handler(5, 1);

		if (action == GLFW_RELEASE) context->handler(5, 0);

		break;
	}

	case GLFW_KEY_E: {
		if (action == GLFW_PRESS) context->handler(6, 1);

		if (action == GLFW_RELEASE) context->handler(6, 0);

		break;
	}

	case GLFW_KEY_R: {
		if (action == GLFW_PRESS) context->handler(0x0D, 1);

		if (action == GLFW_RELEASE) context->handler(0x0D, 0);

		break;
	}

	case GLFW_KEY_A: {
		if (action == GLFW_PRESS) context->handler(7, 1);

		if (action == GLFW_RELEASE) context->handler(7, 0);

		break;
	}

	case GLFW_KEY_S: {
		if (action == GLFW_PRESS) context->handler(8, 1);

		if (action == GLFW_RELEASE) context->handler(8, 0);

		break;
	}

	case GLFW_KEY_D: {
		if (action == GLFW_PRESS) context->handler(9, 1);

		if (action == GLFW_RELEASE) context->handler(9, 1);

		break;
	}

	case GLFW_KEY_F: {
		if (action == GLFW_PRESS) context->handler(0x0E, 1);

		if (action == GLFW_RELEASE) context->handler(0x0E, 0);

		break;
	}

	case GLFW_KEY_Z: {
		if (action == GLFW_PRESS) context->handler(0x0A, 1);

		if (action == GLFW_RELEASE) context->handler(0x0A, 0);

		break;
	}

	case GLFW_KEY_X: {
		if (action == GLFW_PRESS) context->handler(0, 1);

		if (action == GLFW_RELEASE) context->handler(0, 0);

		break;
	}

	case GLFW_KEY_C: {
		if (action == GLFW_PRESS) context->handler(0x0B, 1);

		if (action == GLFW_RELEASE) context->handler(0x0B, 0);

		break;
	}

	case GLFW_KEY_V: {
		if (action == GLFW_PRESS) context->handler(0x0F, 1);

		if (action == GLFW_RELEASE) context->handler(0x0F, 0);

		break;
	}
	}
	default:
		break;
	}
}