#include "keypad-renderer.h"

void KeypadRenderer::initText() {
    g_staticBuf = C2D_TextBufNew(4096);
    C2D_TextParse(&controlText, g_staticBuf, "(Y) - Pause");

}

void KeypadRenderer::render() {
    C2D_TargetClear(screen, clrBlack);
    C2D_SceneBegin(screen);
    
    drawControls();
    highlightPressed();
    drawBorder();
    drawText();
}

void KeypadRenderer::drawControls() {
    C2D_DrawText(&controlText, C2D_WithColor, 0, 225, 0, 0.5f, 0.5f, C2D_Color32f(0.4f,0.4f,0.4f,1.0f));
}

void KeypadRenderer::highlightPressed() {

}

void KeypadRenderer::drawBorder() {
    //Col
    for (int i = 0; i <= 316; i += 79){
        C2D_DrawRectSolid(i, 0, 0, 4, 220, clrWhite);
    }

    //Row
    for (int i = 0; i <= 220; i += 55){
        C2D_DrawRectSolid(0, i, 0, 360, 3, clrWhite);
    }
}

void KeypadRenderer::drawText() {

}