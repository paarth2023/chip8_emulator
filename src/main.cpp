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

    int romSize;

    // display
    u8 display[64 * 32];
} chip8;

void loadRom(u8 memory[], int &setSize)
{
    std::ifstream file("IBM Logo.ch8", std::ios::binary);
    file.seekg(0, file.end);
    int romSize = file.tellg();
    file.seekg(0, file.beg);

    setSize = romSize;

    char *buffer = new char[romSize];

    file.read(buffer, romSize);

    for (int i = 0; i < romSize; i++)
    {
        memory[0x200 + i] = buffer[i];
    }
}

void clearDisplay(u8 *display)
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

    loadRom(emulator.memory, emulator.romSize);

    emulator.pc = 0x200;

    while (1)
    {
        // fetch;
        u16 opcode = (emulator.memory[emulator.pc] << 8) | emulator.memory[emulator.pc + 1];

        // decode
        switch (opcode & 0xF000)
        {
        case 0x0000:
            if (opcode == 0x00E0)
                printf("Clear the screen\n");
            break;
        case 0x1000:
            printf("Jump to address 0x%03X\n", (opcode & 0x0FFF));
            break;
        case 0x6000:
            printf("Set %d to 0x%02X\n", (opcode & 0x0F00), (opcode & 0x00FF));
            break;
        case 0x7000:
            printf("Add 0x%02X to %d\n", (opcode & 0x00FF), (opcode & 0x0F00));
            break;
        case 0xA000:
            printf("Set I to 0x%03X\n", (opcode & 0x0FFF));
            break;
        case 0xD000:
            printf("Draw stuff\n");
            break;
        default:
            break;
        }

        emulator.pc += 2;
    }

    return 0;
}