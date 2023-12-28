#pragma once

#include "3ds.h"
#include "citro2d.h"

#include "keypad-renderer.h"
#include "keypad.h"
#include "top-renderer.h"
#include "speaker.h"

class Chip8 {
private:
    KeypadRenderer keypad_renderer;
    Keypad keypad;
    TopRenderer top_renderer;
    Speaker speaker;
    
    const unsigned int START_ADDRESS = 0x200;
	const unsigned int FONT_START_ADDRESS = 0x50;

	u8 memory[4096] = {};
	u8 v[16] = {};
	u16 i = 0;
	u16 pc = 0x200;
	u8 x = 0x00;
	u8 y = 0x00;
	u16 stack[16] = {};
	u8 stkpt = 0x0;
	u16 opcode = 0x0000;
	u8 delayTimer = 0;
	u8 soundTimer = 0;
	bool isPaused = false;
	int speed = 10;

	u8 getRandomByte();

	void OP_00E0();
	void OP_00EE();
	void OP_1nnn();
	void OP_2nnn();
	void OP_3xkk();
	void OP_4xkk();
	void OP_5xy0();
	void OP_6xkk();
	void OP_7xkk();
	void OP_8xy0();
	void OP_8xy1();
	void OP_8xy2();
	void OP_8xy3();
	void OP_8xy4();
	void OP_8xy5();
	void OP_8xy6();
	void OP_8xy7();
	void OP_8xyE();
	void OP_9xy0();
	void OP_Annn();
	void OP_Bnnn();
	void OP_Cxkk();
	void OP_Dxyn();
	void OP_Ex9E();
	void OP_ExA1();
	void OP_Fx07();
	void OP_Fx0A();
	void OP_Fx15();
	void OP_Fx18();
	void OP_Fx1E();
	void OP_Fx29();
	void OP_Fx33();
	void OP_Fx55();
	void OP_Fx65();

public:
    Chip8 (C3D_RenderTarget* top, C3D_RenderTarget* bottom) {
        top_renderer = TopRenderer(top);
        keypad_renderer = KeypadRenderer(bottom);
        keypad = Keypad(keypad_renderer);

		keypad_renderer.initText();
    };

    void loadFont();
	void loadROM();
	void cycle();
	void executeInstruction();
	void updateTimers();
	void playSound();
};