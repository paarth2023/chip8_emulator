#include "opengl_renderer.h"

#include <cstdint>
#include <fstream>
#include <ios>
#include <iostream>

#define u8 uint8_t
#define u16 uint16_t

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

typedef struct chip8 {
	u8 memory[4096];
	u16 stack[16];
	u8 registers[16];

	// Special registers
	u16 iRegister;
	u16 pc;
	u8 delay;
	u8 sound;
	u8 sPointer;

	int romSize;

	// Display
	u8 display[64 * 32];

	// Opcode
	u16 opcode;

	bool jumpFlag;

	void init() {
		pc = 0x200;
	}

	void setFont() {
		int i = 0;

		for (u8 a = 0x050; a <= 0x09F; a++) {
			memory[a] = font[i];
			i++;
		}
	}

	void clearScreen() {
		for (int i = 0; i < 64 * 32; i++)
			display[i] = 0;
	}

	void loadRom() {
		std::ifstream file("IBM Logo.ch8", std::ios::binary);

		file.seekg(0, file.end);
		int romSize = file.tellg();
		file.seekg(0, file.beg);

		char* buffer = new char[romSize];

		file.read(buffer, romSize);

		for (int i = 0; i < romSize; i++) {
			memory[0x200 + i] = buffer[i];
		}
	}

	void fetch() {
		opcode = (memory[pc] << 8) | memory[pc + 1];
	}

	void decode() {
		jumpFlag = false;

		switch (opcode & 0xF000) {
		case 0x0000:
			if (opcode == 0x00E0)
				clearScreen();

			if (opcode == 0x0000)
				return;

			break;

		case 0x1000:
			pc = (opcode & 0x0FFF);
			jumpFlag = true;
			break;

		case 0x3000: {
			u8 Vx = registers[(opcode & 0x0F00) >> 8];
			u8 kk = opcode & 0x00FF;

			if (Vx == kk)
				pc += 2;

			break;
		}

		case 0x4000: {
			u8 Vx = registers[(opcode & 0x0F00) >> 8];
			u8 kk = opcode & 0x00FF;

			if (Vx != kk)
				pc += 2;

			break;
		}

		case 0x5000: {
			u8 Vx = registers[(opcode & 0x0F00) >> 8];
			u8 Vy = registers[(opcode & 0x00F0) >> 4];

			if (Vx == Vy)
				pc += 2;

			break;
		}

		case 0x6000:
			registers[(opcode & 0x0F00) >> 8] = opcode & 0x00FF;
			break;

		case 0x7000:
			registers[(opcode & 0x0F00) >> 8] += opcode & 0x00FF;
			break;

		case 0x8000: {
			u8 lastDigit = opcode & 0x000F;
			u8* Vx = &registers[(opcode & 0x0F00) >> 8];
			u8* Vy = &registers[(opcode & 0x00F0) >> 4];

			switch (lastDigit) {
			case 0x00:
				*Vx = *Vy;
				break;

			case 0x01:
				*Vx = *Vx | *Vy;
				break;

			case 0x02:
				*Vx = *Vx & *Vy;
				break;

			case 0x03:
				*Vx = *Vx ^ *Vy;
				break;

			case 0x04: {
				u16 sumCarry = *Vx + *Vy;
				u8 carry = sumCarry >> 256;
				u8 sum = sumCarry & 0xFF;

				registers[0xF] = carry;
				*Vx = sum;
				break;
			}

			case 0x05:
				registers[0xF] = (*Vx >= *Vy);
				*Vx = *Vx - *Vy;
				break;

			case 0x06:
				registers[0xF] = *Vx & 1;
				*Vx = *Vx >> 1;
				break;

			case 0x07:
				registers[0xF] = (*Vy >= *Vx);
				*Vx = *Vy - *Vx;
				break;

			case 0x0E:
				registers[0xF] = *Vx & (0b10000000);
				*Vx = *Vx << 1;
				break;

			default:
				break;
			}

			break;
		}

		case 0x9000: {
			u8* Vx = &registers[(opcode & 0x0F00) >> 8];
			u8* Vy = &registers[(opcode & 0x00F0) >> 4];

			if (*Vx != *Vy)
				pc += 2;

			break;
		}

		case 0xA000:
			iRegister = opcode & 0x0FFF;
			break;

		case 0xB000:
			pc = (opcode & 0x0FFF) + registers[0];
			jumpFlag = true;
			break;

		case 0xD000: {
			// DXYN
			auto X = (opcode & 0x0F00) >> 8;
			auto Y = (opcode & 0x00F0) >> 4;

			X = registers[X] & 63;
			Y = registers[Y] & 31;

			registers[0xF] = 0;

			auto N = opcode & 0x000F;

			u8 sprite;

			for (int i = 0; i < N; i++) {
				sprite = memory[iRegister + i];

				for (int j = 7; j >= 0; j--) {
					int bit = (sprite >> j) & 1;

					if (bit == 1) {
						int index = Y * 64 + X;

						if (display[index] == 255)
							registers[0xF] = 1;

						display[index] ^= 255;
					}

					X = (X + 1) % 64;
				}

				X = (opcode & 0x0F00) >> 8;
				X = registers[X] & 63;

				Y = (Y + 1) % 32;
			}

			break;
		}

		default:
			break;
		}

		if (!jumpFlag)
			pc += 2;
	}
} chip8;

int main() {
	OpenGLRenderer renderer(64, 32, 640, 320, "chip-8 emulator");

	if (!renderer.initialize())
		return -1;

	chip8 emulator{};

	emulator.loadRom();
	emulator.init();

	while (!renderer.shouldClose()) {
		// Fetch
		emulator.fetch();

		// Decode
		emulator.decode();

		renderer.render(emulator.display);
		renderer.pollEvents();
	}

	return 0;
}