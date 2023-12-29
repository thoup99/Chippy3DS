#include "chip8.h"

void Chip8::loadFont() {
    u8 fontset[] = {
        0xF0, 0x90, 0x90, 0x90, 0xF0, // 0
        0x20, 0x60, 0x20, 0x20, 0x70, // 1
        0xF0, 0x10, 0xF0, 0x80, 0xF0, // 2
        0xF0, 0x10, 0xF0, 0x10, 0xF0, // 3
        0x90, 0x90, 0xF0, 0x10, 0x10, // 4
        0xF0, 0x80, 0xF0, 0x10, 0xF0, // 5
        0xF0, 0x80, 0xF0, 0x90, 0xF0, // 6
        0xF0, 0x10, 0x20, 0x40, 0x40, // 7
        0xF0, 0x90, 0xF0, 0x90, 0xF0, // 8
        0xF0, 0x90, 0xF0, 0x10, 0xF0, // 9
        0xF0, 0x90, 0xF0, 0x90, 0x90, // A
        0xE0, 0x90, 0xE0, 0x90, 0xE0, // B
        0xF0, 0x80, 0x80, 0x80, 0xF0, // C
        0xE0, 0x90, 0x90, 0x90, 0xE0, // D
        0xF0, 0x80, 0xF0, 0x80, 0xF0, // E
        0xF0, 0x80, 0xF0, 0x80, 0x80  // F
    };

    int offset = 0;
    for (u8 hex : fontset) {
        memory[FONT_START_ADDRESS + offset] = hex;
        offset++;
    }
    
}

void Chip8::loadROM() {
        FILE *file = fopen("romfs:/Tetris.ch8", "rb");
        
        //Get file Size
        fseek(file, 0, SEEK_END);
        int size = ftell(file);
        fseek(file, 0, SEEK_SET);
        
        //Load file into heap memory
        u8* buffer = new u8[size];
        memset(buffer, 0, size);
        fread(buffer, sizeof(u8), size, file);
        fclose(file);

        for (int i = 0; i < size; i++)
        {
            memory[START_ADDRESS + i] = buffer[i];
        }

        delete[] buffer;
}

void Chip8::cycle() {
    for (int i = 0; i < speed; i++)
    {
        if (!isPaused)
        {
            opcode = memory[pc] << 8 | memory[pc + 1];
            x = (opcode & 0x0F00) >> 8;
            y = (opcode & 0x00F0) >> 4;
            executeInstruction();
        }
    }

    if (!isPaused)
    {
        updateTimers();
        playSound();
    }
    
    top_renderer.render();
    keypad_renderer.render();
}

void Chip8::updateTimers() {
    if (delayTimer > 0)
        delayTimer -= 1;

    if (soundTimer > 0)
        soundTimer -= 1;
}

void Chip8::playSound() {

}

void Chip8::handleInput(u32 keys_down) {
    if (keys_down & KEY_Y)
        isPaused = !isPaused;
    keypad.handleTouchInput();
}

u8 Chip8::getRandomByte() {
    return rand() % 255 + 1;
}