#pragma once 

#include <cstdint>
#include <fstream>
#include <iostream>

using u8 = uint8_t;
using u16 = uint16_t;

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

	bool jumpFlag;
	int romSize;

	void init();
	void setFont(u8 font[]);
	void clearScreen();
	void loadRom(const std::string& fileName);
	void fetch();
	void decode();
};