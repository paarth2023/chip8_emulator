#pragma once 

#include <cstdint>
#include <fstream>
#include <iostream>
#include <random>

using u8 = uint8_t;
using u16 = uint16_t;

typedef enum { waitForKey, jump, normal } MODE;

struct Chip8 {
	// emulated structures;
	u8 memory[4096];
	u16 stack[16];
	u8 registers[16];
	u8 keys[16];
	// Special registers
	u16 iRegister;
	u16 pc;
	u8 delay;
	u8 sound;
	u8 sPointer;
	// Display
	u8 display[64 * 32];
	// Opcode
	u16 opcode;
	// mode
	MODE mode;
	// last key pressed
	u8 lastKey;

	size_t romSize;

	// random generator for Cxkk instuction
	std::random_device rd;
	std::mt19937 generator{ rd() };
	std::uniform_int_distribution<int> distribution{ 0, 255 };

	// input handler boolean
	bool keyPressed;

	void init();
	void setFont(u8 font[]);
	void clearScreen();
	void loadRom(const std::string& fileName);
	void updateTimers();
	void fetch();
	void decode();
	void handler(u8 key, u8 state);
};