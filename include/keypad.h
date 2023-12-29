#pragma once
#include "3ds.h"


class Keypad {
private:
	bool keys[16] = {};
	bool is_being_pressed = false;

	int x_pos;
	int y_pos;

public:
	Keypad() {};

	bool isPressed();
	int getXPos() {return x_pos;}
	int getYPos() {return y_pos;}
	
	void handleTouchInput();
	void TouchStopped();
	bool isKeyPressed(int key);
	bool areKeysPressed();
	void SetKeyState(int key, bool state);
	void changeKeyState(int key);
	int getFirstKey();
};