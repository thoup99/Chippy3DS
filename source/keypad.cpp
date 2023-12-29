#include "keypad.h"


void Keypad::handleTouchInput()
{

	touchPosition touch;

	//Read the touch screen coordinates
	hidTouchRead(&touch);

	//Determine which button is being pressed (if any) and pass it to the renderer
	x_pos = touch.px / 80;
	y_pos = touch.py / 55;

	if ((touch.px == 0 && touch.py == 0) || y_pos > 3) {
		if (is_being_pressed) {
			is_being_pressed = false;
			TouchStopped();
		}

	} else {
		//Input is on the keypad
		is_being_pressed = true;
		int button_pressed = (y_pos * 4 + x_pos);
	 	SetKeyState(button_pressed, true);
	}
	
}

void Keypad::TouchStopped() {
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