#include "top-renderer.h"


void TopRenderer::clear() {
	for (int i = 0; i < 2048; i++)
	{
		display[i] = 0;
	}
}

void TopRenderer::render() {
	// Render the scene
    C2D_TargetClear(screen, clrBlack);
	C2D_SceneBegin(screen);

	//Draw Boarder
	C2D_DrawRectSolid(origin_x - BOARDER_WIDTH, origin_y - BOARDER_WIDTH, 0 , display_width + (2 * BOARDER_WIDTH), display_height + (2 * BOARDER_WIDTH), clrBoarder);

	//Draw Black Background
	C2D_DrawRectSolid(origin_x, origin_y, 0, display_width, display_height, clrBlack);

	for (int y = 0; y < 32; y++) 
	{
		for (int x = 0; x < 64; x++) 
		{
			int index = x + (y * 64);
			if (display[index]) 
			{
                C2D_DrawRectSolid(origin_x + (x * SIZE), origin_y + (y * SIZE), 0, SIZE, SIZE, clrWhite);
			}
		}
	}	
}