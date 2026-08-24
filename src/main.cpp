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

u8 font[] = {
    0xF0, 0x90, 0x90, 0x90, 0xF0, // 0
    0x20, 0x60, 0x20, 0x20, 0x70, // 1
    0xF0, 0x10, 0xF0, 0x80, 0xF0, // 2
    0xF0, 0x10, 0xF0, 0x10, 0xF0, // 3
    0x90, 0x90, 0xF0, 0x10, 0x10, // 4
    0xF0, 0x80, 0xF0, 0x10, 0xF0, // 5
    0xF0, 0x80, 0xF0, 0x90, 0xF0, // 6
    0xF0, 0x10, 0x20, 0x40, 0x40, // 7
    0xF0, 0x90, 0xF0, 0x90, 0xF0, // 8
    0xF0, 0x90, 0xF0, 0x10, 0xF0, // 9
    0xF0, 0x90, 0xF0, 0x90, 0x90, // A
    0xE0, 0x90, 0xE0, 0x90, 0xE0, // B
    0xF0, 0x80, 0x80, 0x80, 0xF0, // C
    0xE0, 0x90, 0x90, 0x90, 0xE0, // D
    0xF0, 0x80, 0xF0, 0x80, 0xF0, // E
    0xF0, 0x80, 0xF0, 0x80, 0x80  // F

};

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

    int i = 0;
    for (u8 a = 0x050; a <= 0x09F; a++)
    {
        emulator.memory[a] = font[i];
        i++;
    }

    emulator.pc = 0x200;

    while (!renderer.shouldClose())
    {
        // fetch;
        u16 opcode = (emulator.memory[emulator.pc] << 8) | emulator.memory[emulator.pc + 1];

        // decode
        bool jump = false;
        switch (opcode & 0xF000)
        {
        case 0x0000:
            printf("+++++++++\n");
            if (opcode == 0x00E0)
                clearDisplay(emulator.display);
            if (opcode == 0x0000)
                return 1;
            break;
        case 0x1000:
            printf("---------\n");
            emulator.pc = (opcode & 0x0FFF);
            jump = true;
            break;
        case 0x6000:
            printf("888888888\n");
            emulator.registers[(opcode & 0x0F00) >> 8] = opcode & 0x00FF;
            break;
        case 0x7000:
            printf("77777777\n");
            emulator.registers[(opcode & 0x0F00) >> 8] += opcode & 0x00FF;
            break;
        case 0xA000:
            printf("AAAAAAAA\n");
            emulator.iRegister = opcode & 0x0FFF;
            break;
        case 0xD000:
        {
            // DXYN
            printf("DDDDDDDDDD\n");
            auto X = (opcode & 0x0F00) >> 8;
            auto Y = (opcode & 0x00F0) >> 4;
            X = emulator.registers[X] & 63; // fancy way of doing modulo
            Y = emulator.registers[Y] & 31;

            emulator.registers[0xF] = 0;

            auto N = opcode & 0x000F;

            u8 sprite;
            for (int i = 0; i < N; i++)
            {
                sprite = emulator.memory[emulator.iRegister + i];
                for (int j = 7; j >= 0; j--)
                {
                    int bit = (sprite >> j) & 1;
                    if (bit == 1)
                    {

                        int index = Y * 64 + X;
                        if (emulator.display[index] == 255)
                            emulator.registers[0xF] = 1;
                        emulator.display[index] ^= 255;
                    }
                    X = (X + 1) % 64;
                }

                X = (opcode & 0x0F00) >> 8;
                X = emulator.registers[X] & 63;

                Y = (Y + 1) % 32;
            }
            for (int y = 0; y < 32; y++)
            {
                for (int x = 0; x < 64; x++)
                {
                    printf("%c", emulator.display[y * 64 + x] ? '#' : '.');
                }

                printf("\n");
            }
            break;
        }
        default:
            break;
        }

        if (!jump)
            emulator.pc += 2;
        renderer.render(emulator.display);
        renderer.pollEvents();
    }

    return 0;
}