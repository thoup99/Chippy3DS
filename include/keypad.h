#pragma once
#include "3ds.h"

#include "keypad-renderer.h"


class Keypad {
private:
	bool keys[16] = {};
	bool is_being_pressed = false;

	KeypadRenderer keypad_renderer;

public:
	Keypad() {};
	Keypad(KeypadRenderer kr) {
		keypad_renderer = kr;
	};

	bool isPressed();
	
	void handleTouchInput();
	void handleTouchStop();
	bool isKeyPressed(int key);
	bool areKeysPressed();
	void SetKeyState(int key, bool state);
	void changeKeyState(int key);
	int getFirstKey();
};