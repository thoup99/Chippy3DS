#pragma once

#include "3ds.h"
#include "citro2d.h"


class KeypadRenderer {
private:
    C3D_RenderTarget* screen;

    u32 clrWhite = C2D_Color32(0xFF, 0xFF, 0xFF, 0xFF);
	u32 clrBlack = C2D_Color32(0x00, 0x00, 0x00, 0xFF);
	u32 clrHighlight = C2D_Color32(0x17, 0x17, 0x17, 0xFF);

    C2D_TextBuf g_staticBuf;
    C2D_Text controlText;
    C2D_Text keypadText[16];

    

    void drawControls();
    void drawBorder();
    void highlightPressed();
    void drawText();

public:
    KeypadRenderer() {};
    KeypadRenderer(C3D_RenderTarget* s) {
		screen = s;
	};

    void initText();
    void render();
};