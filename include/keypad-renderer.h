#pragma once

#include "3ds.h"
#include "citro2d.h"

#include "keypad.h"

class KeypadRenderer {
private:
    static const int LINE_WIDTH = 4;
    static const int COLUMN_WIDTH = 79;
    static const int ROW_HEIGHT = 54;

    C3D_RenderTarget* screen;
    Keypad* keypad;

    u32 clrWhite = C2D_Color32(0xFF, 0xFF, 0xFF, 0xFF);
	u32 clrBlack = C2D_Color32(0x00, 0x00, 0x00, 0xFF);
    u32 clrGray = C2D_Color32(0x66, 0x66, 0x66, 0xFF);
	u32 clrHighlight = C2D_Color32(0xb3, 0xb3, 0xb3, 0xFF);

    C2D_TextBuf g_staticBuf;
    C2D_Text controlText;
    C2D_Text keypadText[16];

    int positions[16][2];

    void loadPositions();

    void drawControls();
    void drawBorder();
    void highlightPressed();
    void drawText();

public:
    KeypadRenderer() {};
    KeypadRenderer(C3D_RenderTarget* s, Keypad* kp) {
        keypad = kp;
        screen = s;
        loadPositions();
    }
    //KeypadRenderer(Keypad& k) : keypad{k} {};
    /*KeypadRenderer(C3D_RenderTarget* s, Keypad& k) : keypad{k} {
		screen = s;
        loadPositions();
	};*/

    void initText();
    void render();
};