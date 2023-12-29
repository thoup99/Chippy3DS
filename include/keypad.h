#pragma once
#include "3ds.h"

#include "keypad-renderer.h"

#include <map>

class Keypad {
private:
	int keys[16] = {};
	std::map<int, u8> KEY_MAPPINGS = {
		{1, 0x1}, //1 1
		{2, 0x2}, //2 2
		{3, 0x3}, //3 3
		{4, 0xc}, //4 C
		{5, 0x4}, //Q 4
		{6, 0x5}, //W 5
		{7, 0x6}, //E 6
		{8, 0xD}, //R D
		{9, 0x7}, //A 7
		{10, 0x8}, //S 8
		{11, 0x9}, //D 9
		{12, 0xE}, //F E
		{13, 0xA}, //Z A
		{14, 0x0}, //X 0
		{15, 0xB}, //C B
		{16, 0xF}, //V F
	};

	KeypadRenderer keypad_renderer;

public:
	Keypad() {};
	Keypad(KeypadRenderer kr) {
		keypad_renderer = kr;
	};
	
	void handleTouchInput();
	bool isKeyPressed(int key);
	bool areKeysPressed();
	void changeKeyState(int key);
	int getFirstKey();
};