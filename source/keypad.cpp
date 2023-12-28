#include "keypad.h"


void Keypad::handleInput()
{
	touchPosition touch;

	//Read the touch screen coordinates
	hidTouchRead(&touch);

	int x = touch.px;
	int y = touch.py;

	//Determine which button is being pressed (if any) and pass it to the renderer
	
}

bool Keypad::isKeyPressed(int key) {
	return keys[KEY_MAPPINGS[key]] == 1;
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
	if (KEY_MAPPINGS.find(key) != KEY_MAPPINGS.end())
	{
		keys[KEY_MAPPINGS[key]] ^= 1;
	}
}

int Keypad::getFirstKey() {
	for (int i = 0; i < 16; i++) {
		if (keys[i] == 1)
			return i + 1;
	}
	return 0x0;
}