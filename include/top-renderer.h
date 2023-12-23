#pragma once
#include <3ds.h>
#include <citro2d.h>

class TopRenderer {
private:
	static const int SIZE = 6;
	static const int BOARDER_WIDTH = 3;

    int origin_x = 8;
    int origin_y = 24;

	int display_width = 384;
	int display_height = 192;

	int cols = 64;
	int rows = 32;
	short display [64 * 32] = {};

    u32 clrWhite = C2D_Color32(0xFF, 0xFF, 0xFF, 0xFF);
	u32 clrBlack = C2D_Color32(0x00, 0x00, 0x00, 0xFF);
	u32 clrBoarder = C2D_Color32(0x17, 0x17, 0x17, 0xFF);

	C3D_RenderTarget* screen;

public:
	TopRenderer() {};
	TopRenderer(C3D_RenderTarget* s) {
		screen = s;
	};

	void clear();
	bool setPixel(int x, int y);
	void render();
};