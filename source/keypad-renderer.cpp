#include "keypad-renderer.h"


void KeypadRenderer::loadPositions() {
    for (int y = 0; y <= 4; y++) {
        for (int x = 0; x <= 4; x++) {
            int i = y * 4 + x;
            positions[i][0] = (x * COLUMN_WIDTH) + 34;
            positions[i][1] = (y * ROW_HEIGHT) + 16;
        }
    }
}

void KeypadRenderer::initText() {
    g_staticBuf = C2D_TextBufNew(4096);
    C2D_TextParse(&controlText, g_staticBuf, "(Y) - Pause     (X) - Open ROM Browser");
    C2D_TextOptimize(&controlText);

    const char* text[] = {
        "1", "2", "3", "C",
        "4", "5", "6", "D",
        "7", "8", "9", "E",
        "A", "0", "B", "F"
    };

    for (int x = 0; x < 16; x++) {
        C2D_TextParse(&keypadText[x], g_staticBuf, text[x]);
        C2D_TextOptimize(&keypadText[x]);
    }
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
    C2D_DrawText(&controlText, C2D_WithColor, 0, 225, 0, 0.5f, 0.5f, clrGray);
}

void KeypadRenderer::highlightPressed() {

}

void KeypadRenderer::drawBorder() {
    //Col
    for (int i = 0; i <= 316; i += COLUMN_WIDTH){
        C2D_DrawRectSolid(i, 0, 0, LINE_WIDTH, 220, clrWhite);
    }

    //Row
    for (int i = 0; i <= 216; i += ROW_HEIGHT){
        C2D_DrawRectSolid(0, i, 0, 360, LINE_WIDTH, clrWhite);
    }
}

void KeypadRenderer::drawText() {
    for (int x = 0; x < 16; x++)
        C2D_DrawText(&keypadText[x], C2D_WithColor, positions[x][0], positions[x][1], 0, 1, 1, clrWhite);
}