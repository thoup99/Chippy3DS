#include "keypad.h"


void Keypad::handleTouchInput()
{
	touchPosition touch;

	//Read the touch screen coordinates
	hidTouchRead(&touch);

	int x = touch.px;
	int y = touch.py;

	//Determine which button is being pressed (if any) and pass it to the renderer
	
}

bool Keypad::isKeyPressed(int key) {
	return keys[key] == 1;
}

bool Keypad::areKeysPressed() {
	for (int k : keys)
	{
		if (k == 1)
			return true;
	}
	return false;
}

void Keypad::changeKeyState(int key)
{
	keys[key] ^= 1;
}

int Keypad::getFirstKey() {
	for (int i = 0; i < 16; i++) {
		if (keys[i] == 1)
			return i;
	}
	return 0x0;
}