#include "keypad.h"


void Keypad::handleTouchInput()
{
	is_being_pressed = true;

	touchPosition touch;

	//Read the touch screen coordinates
	hidTouchRead(&touch);

	int x = touch.px;
	int y = touch.py;

	//Determine which button is being pressed (if any) and pass it to the renderer
	int x_pos = x / 80;
	int y_pos = y / 55;

	//If y > 3 then the input is happening below the keypad and should be ignored
	if (y > 3) {
		int button_pressed = (y_pos * 4 + x_pos);
	 	SetKeyState(button_pressed, true);
	}
	
}

void Keypad::handleTouchStop() {
	is_being_pressed = false;

	for (bool &k : keys)
		k = false;

}

bool Keypad::isPressed() {
	return is_being_pressed;
}

bool Keypad::isKeyPressed(int key) {
	return keys[key];
}

bool Keypad::areKeysPressed() {
	for (bool k: keys){
		if (k) return true;
	}
	return false;
}

void Keypad::SetKeyState(int key, bool state){
	keys[key] = state;
}

void Keypad::changeKeyState(int key)
{
	keys[key] ^= 1;
}

int Keypad::getFirstKey() {
	for (int i = 0; i <= 15; i++) {
		if (keys[i])
			return i; // If something breaks add a + 1 here
	}
	return 0x0;
}