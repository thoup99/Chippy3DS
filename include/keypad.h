#pragma once
#include "3ds.h"

#include "keypad-renderer.h"


class Keypad {
private:
	int keys[16] = {};

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