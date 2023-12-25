#pragma once

#include "3ds.h"
#include "citro2d.h"

#include "keypad-renderer.h"
#include "keypad.h"
#include "top-renderer.h"
#include "speaker.h"
#include "cpu.h"

class Chip8 {
private:
    KeypadRenderer keypad_renderer;
    Keypad keypad;
    TopRenderer top_renderer;
    Speaker speaker;
    Cpu cpu;
public:
    Chip8 (C3D_RenderTarget* top, C3D_RenderTarget* bottom) {
        top_renderer = TopRenderer(top);
        keypad_renderer = KeypadRenderer(bottom);
        cpu = Cpu(top_renderer, keypad, speaker);
    };
};