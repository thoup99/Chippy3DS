#pragma once
#include "3ds.h"

#include "keypad-renderer.h"

#include <iostream>
#include <map>
#include <cstdint>

using namespace std;

class Keypad {
private:
	int keys[16] = {};
	map<int, uint8_t> KEY_MAPPINGS = {
		{49, 0x1}, //1 1
		{50, 0x2}, //2 2
		{51, 0x3}, //3 3
		{52, 0xc}, //4 C
		{81, 0x4}, //Q 4
		{87, 0x5}, //W 5
		{69, 0x6}, //E 6
		{82, 0xD}, //R D
		{65, 0x7}, //A 7
		{83, 0x8}, //S 8
		{68, 0x9}, //D 9
		{70, 0xE}, //F E
		{90, 0xA}, //Z A
		{88, 0x0}, //X 0
		{67, 0xB}, //C B
		{76, 0xF}, //V F
	};

	KeypadRenderer keypad_renderer;

public:
	Keypad() {};
	Keypad(KeypadRenderer kr) {
		keypad_renderer = kr;
	};
	
	void handleInput();
	bool isKeyPressed(int key);
	bool areKeysPressed();
	void changeKeyState(int key);
	int getFirstKey();
};