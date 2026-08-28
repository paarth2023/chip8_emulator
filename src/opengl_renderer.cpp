#include "opengl_renderer.h"

#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include <iostream>

namespace
{
	const char* vertexShaderSource = R"(
#version 330 core

layout (location = 0) in vec3 aPos;
layout (location = 1) in vec2 aTexCoord;

out vec2 TexCoord;

void main()
{
    gl_Position = vec4(aPos, 1.0);
    TexCoord = aTexCoord;
}
)";

	const char* fragmentShaderSource = R"(
#version 330 core

in vec2 TexCoord;

out vec4 FragColor;

uniform sampler2D screenTexture;

void main()
{
    float pixel = texture(screenTexture, TexCoord).r;
    vec3 darkGreen = vec3(0.0, 0.5, 0.0);
    FragColor = vec4(darkGreen * pixel, 1.0);
}
)";

	unsigned int compileShader(unsigned int type, const char* source)
	{
		unsigned int shader = glCreateShader(type);
		glShaderSource(shader, 1, &source, nullptr);
		glCompileShader(shader);

		int success = 0;
		glGetShaderiv(shader, GL_COMPILE_STATUS, &success);
		if (!success)
		{
			char infoLog[512] = {};
			glGetShaderInfoLog(shader, sizeof(infoLog), nullptr, infoLog);
			std::cerr << "OpenGL shader compilation failed: " << infoLog << '\n';
			glDeleteShader(shader);
			return 0;
		}
		return shader;
	}

	unsigned int createShaderProgram()
	{
		const unsigned int vertexShader = compileShader(GL_VERTEX_SHADER, vertexShaderSource);
		const unsigned int fragmentShader = compileShader(GL_FRAGMENT_SHADER, fragmentShaderSource);
		if (vertexShader == 0 || fragmentShader == 0)
		{
			glDeleteShader(vertexShader);
			glDeleteShader(fragmentShader);
			return 0;
		}

		const unsigned int program = glCreateProgram();
		glAttachShader(program, vertexShader);
		glAttachShader(program, fragmentShader);
		glLinkProgram(program);

		int success = 0;
		glGetProgramiv(program, GL_LINK_STATUS, &success);
		if (!success)
		{
			char infoLog[512] = {};
			glGetProgramInfoLog(program, sizeof(infoLog), nullptr, infoLog);
			std::cerr << "OpenGL shader linking failed: " << infoLog << '\n';
			glDeleteProgram(program);
			glDeleteShader(vertexShader);
			glDeleteShader(fragmentShader);
			return 0;
		}

		glDeleteShader(vertexShader);
		glDeleteShader(fragmentShader);
		return program;
	}
}

OpenGLRenderer::OpenGLRenderer(int displayWidth, int displayHeight, int windowWidth, int windowHeight, const char* title)
	: displayWidth(displayWidth), displayHeight(displayHeight), windowWidth(windowWidth), windowHeight(windowHeight), title(title)
{
}

OpenGLRenderer::~OpenGLRenderer()
{
	release();
}

bool OpenGLRenderer::initialize()
{
	if (!glfwInit())
	{
		std::cerr << "Failed to initialize GLFW\n";
		return false;
	}

	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

	window = glfwCreateWindow(windowWidth, windowHeight, title, nullptr, nullptr);
	if (window == nullptr)
	{
		std::cerr << "Failed to create GLFW window\n";
		glfwTerminate();
		return false;
	}

	glfwMakeContextCurrent(window);
	glfwSetWindowUserPointer(window, this);
	glfwSetFramebufferSizeCallback(window, framebufferSizeCallback);

	if (!gladLoadGLLoader(reinterpret_cast<GLADloadproc>(glfwGetProcAddress)))
	{
		std::cerr << "Failed to initialize GLAD\n";
		release();
		return false;
	}
	gladLoaded = true;

	shaderProgram = createShaderProgram();
	if (shaderProgram == 0)
	{
		release();
		return false;
	}

	const float vertices[] = {
		-1.0f, -1.0f, 0.0f, 0.0f, 1.0f,
		1.0f, -1.0f, 0.0f, 1.0f, 1.0f,
		1.0f, 1.0f, 0.0f, 1.0f, 0.0f,
		-1.0f, 1.0f, 0.0f, 0.0f, 0.0f };
	const unsigned int indices[] = { 0, 1, 2, 2, 3, 0 };

	glGenVertexArrays(1, &vertexArray);
	glGenBuffers(1, &vertexBuffer);
	glGenBuffers(1, &elementBuffer);
	glBindVertexArray(vertexArray);
	glBindBuffer(GL_ARRAY_BUFFER, vertexBuffer);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, elementBuffer);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 5 * sizeof(float), nullptr);
	glEnableVertexAttribArray(0);
	glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 5 * sizeof(float), reinterpret_cast<void*>(3 * sizeof(float)));
	glEnableVertexAttribArray(1);

	glGenTextures(1, &texture);
	glBindTexture(GL_TEXTURE_2D, texture);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RED, displayWidth, displayHeight, 0, GL_RED, GL_UNSIGNED_BYTE, nullptr);

	glUseProgram(shaderProgram);
	glUniform1i(glGetUniformLocation(shaderProgram, "screenTexture"), 0);
	return true;
}

bool OpenGLRenderer::shouldClose() const
{
	return window == nullptr || glfwWindowShouldClose(window);
}

void OpenGLRenderer::render(const std::uint8_t* display)
{
	if (window == nullptr || display == nullptr)
		return;

	glClear(GL_COLOR_BUFFER_BIT);
	glUseProgram(shaderProgram);
	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_2D, texture);
	glTexSubImage2D(GL_TEXTURE_2D, 0, 0, 0, displayWidth, displayHeight, GL_RED, GL_UNSIGNED_BYTE, display);
	glBindVertexArray(vertexArray);
	glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, nullptr);
	glfwSwapBuffers(window);
}

void OpenGLRenderer::pollEvents()
{
	glfwPollEvents();
}

void OpenGLRenderer::release()
{
	if (window != nullptr)
	{
		glfwMakeContextCurrent(window);
		if (gladLoaded)
		{
			glDeleteTextures(1, &texture);
			glDeleteBuffers(1, &elementBuffer);
			glDeleteBuffers(1, &vertexBuffer);
			glDeleteVertexArrays(1, &vertexArray);
			glDeleteProgram(shaderProgram);
		}
		glfwDestroyWindow(window);
		window = nullptr;
		glfwTerminate();
	}
}

void OpenGLRenderer::framebufferSizeCallback(GLFWwindow*, int width, int height)
{
	glViewport(0, 0, width, height);
}

void OpenGLRenderer::setKeyCallback(GLFWkeyfun callback) {
	glfwSetKeyCallback(window, callback);
}