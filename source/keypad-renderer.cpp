#include "keypad-renderer.h"

void KeypadRenderer::initText() {
    g_staticBuf = C2D_TextBufNew(4096);
    C2D_TextParse(&g_staticText, g_staticBuf, "Hello World");
}

void KeypadRenderer::render() {
    C2D_TargetClear(screen, clrWhite);
    C2D_SceneBegin(screen);
    C2D_DrawText(&g_staticText, C2D_WithColor, 8.0f, 8.0f, 0.0f, 1.0f, 1.0f, C2D_Color32f(1.0f,0.0f,0.0f,1.0f));
}