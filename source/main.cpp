// Simple citro2d untextured shape example
#include <3ds.h>
#include <citro2d.h>

#include "cpu.h"
#include "keypad.h"
#include "top-renderer.h"
#include "speaker.h"

#include <string.h>
#include <stdio.h>
#include <stdlib.h>


#define SCREEN_WIDTH  400
#define SCREEN_HEIGHT 240

//---------------------------------------------------------------------------------
int main(int argc, char* argv[]) {
//---------------------------------------------------------------------------------
	// Init libs
	romfsInit();
	gfxInitDefault();
	C3D_Init(C3D_DEFAULT_CMDBUF_SIZE);
	C2D_Init(C2D_DEFAULT_MAX_OBJECTS);
	C2D_Prepare();

	// Create screens
	C3D_RenderTarget* top = C2D_CreateScreenTarget(GFX_TOP, GFX_LEFT);
	C3D_RenderTarget* bottom = C2D_CreateScreenTarget(GFX_BOTTOM, GFX_LEFT);

	//Create Objects
	Keypad keypad;
	TopRenderer renderer(top);
	Speaker speaker;
	Cpu cpu(renderer, keypad, speaker);

	//load rom into memory
	cpu.loadFont();
	cpu.loadROM();

	u32 clrWhite = C2D_Color32(0xFF, 0xFF, 0xFF, 0xFF);
	u32 clrBlack = C2D_Color32(0x00, 0x00, 0x00, 0xFF);

	// Main loop
	while (aptMainLoop())
	{
		hidScanInput();

		// Respond to user input
		u32 kDown = hidKeysDown();
		if (kDown & KEY_START)
			break; // break in order to return to hbmenu


		//Begin Drawing to Screens
		C3D_FrameBegin(C3D_FRAME_SYNCDRAW);

		//Cycle the Cpu
		keypad.handleInput();
		cpu.cycle();

		//Draw the Bottom Screen
		C2D_TargetClear(bottom, clrWhite);
		C2D_SceneBegin(bottom);
		C2D_DrawRectSolid(20,30,0,100,60,clrBlack);


		C3D_FrameEnd(0);
	}

	// Deinit libs
	C2D_Fini();
	C3D_Fini();
	gfxExit();
	return 0;
}