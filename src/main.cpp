#include "opengl_renderer.h"

#include <fstream>
#include <ios>
#include <iostream>
#include <cstdint>

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

void clearDisplay(uint8_t *display)
{
    for (int i = 0; i < 64 * 32; i++)
    {
        display[i] = 0;
    }
}

int main()
{
    OpenGLRenderer renderer(64, 32, 640, 320, "chip-8 emulator");
    if (!renderer.initialize())
        return -1;

    chip8 emulator{};

    while (!renderer.shouldClose())
    {
        renderer.render(emulator.display);
        renderer.pollEvents();
    }

    return 0;
}