#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <fstream>
#include <ios>
#include <iostream>
#include <cstdint>
#include <stdio.h>

#define u8 uint8_t
#define u16 uint16_t

typedef struct chip8
{
    u8 memory[4096];
    u16 stack[16]; // stack;
    u8 registers[16];

    // special registers
    u16 iRegister;
    u16 pc;      // program counter
    u8 delay;    // delay timer
    u8 sound;    // sound timer
    u8 sPointer; // stack pointer

    // display
    u8 display[64 * 32];
} chip8;

const char *vertexShaderSource = R"(
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

const char *fragmentShaderSource = R"(
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
void clearDisplay(uint8_t *display)
{
    for (int i = 0; i < 64 * 32; i++)
    {
        display[i] = 0;
    }
}
void testCheckerboard(uint8_t *display)
{
    clearDisplay(display);

    for (int y = 0; y < 32; y++)
    {
        for (int x = 0; x < 64; x++)
        {
            if ((x + y) % 2 == 0)
                display[y * 64 + x] = 255;
        }
    }
}
void testSprite(uint8_t *display)
{
    clearDisplay(display);

    uint8_t sprite[] =
        {
            0b10011001,
            0b01100110,
            0b00111100,
            0b11111111,
            0b00111100,
            0b01100110,
            0b10011001};

    int x = 20;
    int y = 10;

    for (int row = 0; row < 7; row++)
    {
        for (int bit = 0; bit < 8; bit++)
        {
            if (sprite[row] & (0x80 >> bit))
            {
                display[(y + row) * 64 + (x + bit)] = 255;
            }
        }
    }
}

int main()
{
    glfwInit();
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    GLFWwindow *window = glfwCreateWindow(640, 320, "chip-8 emulator", NULL, NULL);
    if (window == NULL)
    {
        printf("OPENGL ERROR\n");
        glfwTerminate();
        return -1;
    }
    glfwMakeContextCurrent(window);
    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
    {
        printf("GLAD ERROR\n");
        return -1;
    }
    glViewport(0, 0, 640, 320);
    unsigned int vertexShader;
    vertexShader = glCreateShader(GL_VERTEX_SHADER);
    glShaderSource(vertexShader, 1, &vertexShaderSource, NULL);
    glCompileShader(vertexShader);

    unsigned int fragmentShader;
    fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
    glShaderSource(fragmentShader, 1, &fragmentShaderSource, NULL);
    glCompileShader(fragmentShader);

    unsigned int shaderProgram;
    shaderProgram = glCreateProgram();
    glAttachShader(shaderProgram, vertexShader);
    glAttachShader(shaderProgram, fragmentShader);
    glLinkProgram(shaderProgram);

    float vertices[] =
        {
            // Position          // Texture
            -1.0f, -1.0f, 0.0f, 0.0f, 0.0f, // Bottom-left
            1.0f, -1.0f, 0.0f, 1.0f, 0.0f,  // Bottom-right
            1.0f, 1.0f, 0.0f, 1.0f, 1.0f,   // Top-right
            -1.0f, 1.0f, 0.0f, 0.0f, 1.0f   // Top-left
        };
    unsigned int indices[] =
        {
            0, 1, 2,
            2, 3, 0};
    unsigned int VAO;
    unsigned int VBO;
    unsigned int EBO;

    glGenVertexArrays(1, &VAO);
    glGenBuffers(1, &VBO);
    glGenBuffers(1, &EBO);

    glBindVertexArray(VAO);
    glBindBuffer(GL_ARRAY_BUFFER, VBO);

    glBufferData(
        GL_ARRAY_BUFFER,
        sizeof(vertices),
        vertices,
        GL_STATIC_DRAW);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);

    glBufferData(
        GL_ELEMENT_ARRAY_BUFFER,
        sizeof(indices),
        indices,
        GL_STATIC_DRAW);
    glVertexAttribPointer(
        0,
        3,
        GL_FLOAT,
        GL_FALSE,
        5 * sizeof(float),
        (void *)0);

    glEnableVertexAttribArray(0);
    glVertexAttribPointer(
        1,
        2,
        GL_FLOAT,
        GL_FALSE,
        5 * sizeof(float),
        (void *)(3 * sizeof(float)));

    glEnableVertexAttribArray(1);

    chip8 *emulator = new chip8();
    testSprite(emulator->display);

    GLuint texture;
    glGenTextures(1, &texture);
    glBindTexture(GL_TEXTURE_2D, texture);
    glTexImage2D(
        GL_TEXTURE_2D,
        0,
        GL_RED,
        64,
        32,
        0,
        GL_RED,
        GL_UNSIGNED_BYTE,
        emulator->display);

    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);

    glActiveTexture(GL_TEXTURE0);
    glBindTexture(GL_TEXTURE_2D, texture);

    glUseProgram(shaderProgram);
    glUniform1i(glGetUniformLocation(shaderProgram, "screenTexture"), 0);

    while (!glfwWindowShouldClose(window))
    {
        glClear(GL_COLOR_BUFFER_BIT);
        glUseProgram(shaderProgram);

        glBindTexture(GL_TEXTURE_2D, texture);
        glTexSubImage2D(
            GL_TEXTURE_2D,
            0,
            GL_RED,
            64,
            32,
            0,
            GL_RED,
            GL_UNSIGNED_BYTE,
            emulator->display);

        glBindVertexArray(VAO);

        glDrawElements(
            GL_TRIANGLES,
            6,
            GL_UNSIGNED_INT,
            0);
        glfwSwapBuffers(window);
        glfwPollEvents();
    }
    return 0;
}