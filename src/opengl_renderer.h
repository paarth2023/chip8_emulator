#pragma once

#include <cstdint>

struct GLFWwindow;
typedef void(*GLFWkeyfun) (GLFWwindow* window, int key, int scancode, int action, int mods);

class OpenGLRenderer
{
public:
	OpenGLRenderer(int displayWidth, int displayHeight, int windowWidth, int windowHeight, const char* title);
	~OpenGLRenderer();

	OpenGLRenderer(const OpenGLRenderer&) = delete;
	OpenGLRenderer& operator=(const OpenGLRenderer&) = delete;

	bool initialize();
	bool shouldClose() const;
	void render(const std::uint8_t* display);
	void pollEvents();

	// non ai feature
	void setKeyCallback(GLFWkeyfun callback);
	void setUserPointer(void* ptr);

private:
	void release();
	static void framebufferSizeCallback(GLFWwindow* window, int width, int height);

	int displayWidth;
	int displayHeight;
	int windowWidth;
	int windowHeight;
	const char* title;
	GLFWwindow* window = nullptr;
	unsigned int shaderProgram = 0;
	unsigned int vertexArray = 0;
	unsigned int vertexBuffer = 0;
	unsigned int elementBuffer = 0;
	unsigned int texture = 0;
	bool gladLoaded = false;
};