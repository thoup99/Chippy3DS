#pragma once

#include "3ds.h"
#include "citro2d.h"

class KeypadRenderer {
private:
    C3D_RenderTarget* screen;

    u32 clrWhite = C2D_Color32(0xFF, 0xFF, 0xFF, 0xFF);
	u32 clrBlack = C2D_Color32(0x00, 0x00, 0x00, 0xFF);
	u32 clrBoarder = C2D_Color32(0x17, 0x17, 0x17, 0xFF);

public:
    KeypadRenderer() {};
    KeypadRenderer(C3D_RenderTarget* s) {
		screen = s;
	};

    void render();
};