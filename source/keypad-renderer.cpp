#include "keypad-renderer.h"

void KeypadRenderer::render() {
    C2D_TargetClear(screen, clrWhite);
    C2D_SceneBegin(screen);
    C2D_DrawRectSolid(20,30,0,100,60,clrBlack);
}