#include "keyboard.h"
#include "chip8.h"

void keyboard::keyCallback(GLFWwindow* window, int key, int scanmode, int action, int mods)
{
	Chip8* context = static_cast<Chip8*>(glfwGetWindowUserPointer(window));


	switch (key)
	{
	case GLFW_KEY_1:
	{
		if (action == GLFW_PRESS)
		{
			context->handler(1, 1);
			context->lastKey = 1;
		}

		if (action == GLFW_RELEASE)
		{
			context->handler(1, 0);
		}

		break;
	}

	case GLFW_KEY_2:
	{
		if (action == GLFW_PRESS)
		{
			context->handler(2, 1);
			context->lastKey = 2;
		}

		if (action == GLFW_RELEASE)
		{
			context->handler(2, 0);
		}

		break;
	}

	case GLFW_KEY_3:
	{
		if (action == GLFW_PRESS)
		{
			context->handler(3, 1);
			context->lastKey = 3;
		}

		if (action == GLFW_RELEASE)
		{
			context->handler(3, 0);
		}

		break;
	}

	case GLFW_KEY_4:
	{
		if (action == GLFW_PRESS)
		{
			context->handler(0x0C, 1);
			context->lastKey = 0x0C;
		}

		if (action == GLFW_RELEASE)
		{
			context->handler(0x0C, 0);
		}

		break;
	}

	case GLFW_KEY_Q:
	{
		if (action == GLFW_PRESS)
		{
			context->handler(4, 1);
			context->lastKey = 4;
		}

		if (action == GLFW_RELEASE)
		{
			context->handler(4, 0);
		}

		break;
	}

	case GLFW_KEY_W:
	{
		if (action == GLFW_PRESS)
		{
			context->handler(5, 1);
			context->lastKey = 5;
		}

		if (action == GLFW_RELEASE)
		{
			context->handler(5, 0);
		}

		break;
	}

	case GLFW_KEY_E:
	{
		if (action == GLFW_PRESS)
		{
			context->handler(6, 1);
			context->lastKey = 6;
		}

		if (action == GLFW_RELEASE)
		{
			context->handler(6, 0);
		}

		break;
	}

	case GLFW_KEY_R:
	{
		if (action == GLFW_PRESS)
		{
			context->handler(0x0D, 1);
			context->lastKey = 0x0D;
		}

		if (action == GLFW_RELEASE)
		{
			context->handler(0x0D, 0);
		}

		break;
	}

	case GLFW_KEY_A:
	{
		if (action == GLFW_PRESS)
		{
			context->handler(7, 1);
			context->lastKey = 7;
		}

		if (action == GLFW_RELEASE)
		{
			context->handler(7, 0);
		}

		break;
	}

	case GLFW_KEY_S:
	{
		if (action == GLFW_PRESS)
		{
			context->handler(8, 1);
			context->lastKey = 8;
		}

		if (action == GLFW_RELEASE)
		{
			context->handler(8, 0);
		}

		break;
	}

	case GLFW_KEY_D:
	{
		if (action == GLFW_PRESS)
		{
			context->handler(9, 1);
			context->lastKey = 9;
		}

		if (action == GLFW_RELEASE)
		{
			context->handler(9, 0);
		}

		break;
	}

	case GLFW_KEY_F:
	{
		if (action == GLFW_PRESS)
		{
			context->handler(0x0E, 1);
			context->lastKey = 0x0E;
		}

		if (action == GLFW_RELEASE)
		{
			context->handler(0x0E, 0);
		}

		break;
	}

	case GLFW_KEY_Z:
	{
		if (action == GLFW_PRESS)
		{
			context->handler(0x0A, 1);
			context->lastKey = 0x0A;
		}

		if (action == GLFW_RELEASE)
		{
			context->handler(0x0A, 0);
		}

		break;
	}

	case GLFW_KEY_X:
	{
		if (action == GLFW_PRESS)
		{
			context->handler(0, 1);
			context->lastKey = 0;
		}

		if (action == GLFW_RELEASE)
		{
			context->handler(0, 0);
		}

		break;
	}

	case GLFW_KEY_C:
	{
		if (action == GLFW_PRESS)
		{
			context->handler(0x0B, 1);
			context->lastKey = 0x0B;
		}

		if (action == GLFW_RELEASE)
		{
			context->handler(0x0B, 0);
		}

		break;
	}

	case GLFW_KEY_V:
	{
		if (action == GLFW_PRESS)
		{
			context->handler(0x0F, 1);
			context->lastKey = 0x0F;
		}

		if (action == GLFW_RELEASE)
		{
			context->handler(0x0F, 0);
		}

		break;
	}

	default:
		break;
	}
}