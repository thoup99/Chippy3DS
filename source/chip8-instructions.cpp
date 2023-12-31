#include "chip8.h"

void Chip8::executeInstruction() {
    pc += 2;

    switch (opcode & 0xF000) {
        case 0x0000:
            switch (opcode) {
                case 0x00E0:
                    OP_00E0();
                    break;

                case 0x00EE:
                    OP_00EE();
                    break;
            }
            break;

        case 0x1000:
            OP_1nnn();
            break;

        case 0x2000:
            OP_2nnn();
            break;

        case 0x3000:
            OP_3xkk();
            break;

        case 0x4000:
            OP_4xkk();
            break;

        case 0x5000:
            OP_5xy0();
            break;

        case 0x6000:
            OP_6xkk();
            break;

        case 0x7000:
            OP_7xkk();
            break;

        case 0x8000:
            switch (opcode & 0xF) {
                case 0x0:
                    OP_8xy0();
                    break;

                case 0x1:
                    OP_8xy1();
                    break;

                case 0x2:
                    OP_8xy2();
                    break;

                case 0x3:
                    OP_8xy3();
                    break;

                case 0x4:
                    OP_8xy4();
                    break;

                case 0x5:
                    OP_8xy5();
                    break;

                case 0x6:
                    OP_8xy6();
                    break;

                case 0x7:
                    OP_8xy7();
                    break;

                case 0xE:
                    OP_8xyE();
                    break;
            }

            break;

        case 0x9000:
            OP_9xy0();
            break;

        case 0xA000:
            OP_Annn();
            break;

        case 0xB000:
            OP_Bnnn();
            break;

        case 0xC000:
            OP_Cxkk();
            break;

        case 0xD000:
            OP_Dxyn();
            break;

        case 0xE000:
            switch (opcode & 0xFF) {
                case 0x9E:
                    OP_Ex9E();
                    break;

                case 0xA1:
                    OP_ExA1();
                    break;
            }

            break;
        case 0xF000:
            switch (opcode & 0xFF) {
                case 0x07:
                    OP_Fx07();
                    break;
                    
                case 0x0A:
                    OP_Fx0A();
                    break;

                case 0x15:
                    OP_Fx15();
                    break;

                case 0x18:
                    OP_Fx18();
                    break;

                case 0x1E:
                    OP_Fx1E();
                    break;

                case 0x29:
                    OP_Fx29();
                    break;

                case 0x33:
                    OP_Fx33();
                    break;

                case 0x55:
                    OP_Fx55();
                    break;

                case 0x65:
                    OP_Fx65();
                    break;
            }
            break;
    }
}

void Chip8::OP_00E0() {
    top_renderer.clear();
}

void Chip8::OP_00EE()//
{
    stkpt--;
    pc = stack[stkpt];
}

void Chip8::OP_1nnn()
{
    pc = (opcode & 0xFFF);
}

void Chip8::OP_2nnn() //
{
    stack[stkpt] = pc;
    stkpt++;

    pc = (opcode & 0xFFF);
}

void Chip8::OP_3xkk() {
    if (v[x] == (opcode & 0xFF))
        pc += 2;
}

void Chip8::OP_4xkk() {
    if (v[x] != (opcode & 0xFF))
        pc += 2;
}

void Chip8::OP_5xy0() {
    if (v[x] == v[y])
        pc += 2;
}

void Chip8::OP_6xkk()
{
    v[x] = (opcode & 0xFF);
}

void Chip8::OP_7xkk()
{
    v[x] += (opcode & 0xFF);
}

void Chip8::OP_8xy0() {
    v[x] = v[y];
}

void Chip8::OP_8xy1(){
    v[x] |= v[y];
}

void Chip8::OP_8xy2() {
    v[x] &= v[y];
}

void Chip8::OP_8xy3() {
    v[x] ^= v[y];
}

void Chip8::OP_8xy4() {
    u16 sum = v[x] + v[y];

    v[0xF] = 0;

    if (sum > 0xFF)
        v[0xF] = 1;

    v[x] = sum & 0xFF;
}

void Chip8::OP_8xy5() {
    v[0xF] = 0;

    if (v[x] > v[y])
        v[0xF] = 1;

    v[x] -= v[y];
}

void Chip8::OP_8xy6() {
    v[0xF] = (v[x] & 0x1);

    v[x] >>= 1;
}

void Chip8::OP_8xy7() {
    v[0xF] = 0;       

    if (v[y] > v[x])
        v[0xF] = 1;

    v[x] = v[y] - v[x];
}

void Chip8::OP_8xyE() {
    v[0xF] = (v[x] & 0x80);
    v[x] <<= 1;
}

void Chip8::OP_9xy0() {
    if (v[x] != v[y])
        pc += 2;
}

void Chip8::OP_Annn()
{
    i = (opcode & 0xFFF);
}

void Chip8::OP_Bnnn() {
    pc = (opcode & 0xFFF) + v[0x0];
}

void Chip8::OP_Cxkk() {
    u8 byte = opcode & 0xFF;
    v[x] = getRandomByte() & byte;
}

void Chip8::OP_Dxyn()
{
    //I could not have gotten this without help from Austin Morlan's guide
    //The code below is a slightly modified version of what is used in his chip-8 emulator
    
    int height = (opcode & 0x000F);

    v[0xF] = 0;

    u8 xPos = v[x] % top_renderer.WIDTH;
    u8 yPos = v[y] % top_renderer.HEIGHT;

    for (int row = 0; row < height; ++row)
    {
        u8 sprite_byte = memory[i + row];

        for (int col = 0; col < 8; ++col)
        {
            u8 sprite_pixel = sprite_byte & (0x80 >> col);
            bool* screen_pixel = &top_renderer.display[(yPos + row) * top_renderer.WIDTH + (xPos + col)];

            if (sprite_pixel)
            {
                if (*screen_pixel)
                {
                    v[0xF] = 1;
                }

                *screen_pixel ^= 1;
            }
        }        
    }
}

void Chip8::OP_Ex9E() {
    if (keypad.isKeyPressed(v[x]))
        pc += 2;
}

void Chip8::OP_ExA1(){
    if (!keypad.isKeyPressed(v[x]))
        pc += 2;
}

void Chip8::OP_Fx07() {
    v[x] = delayTimer;
}

void Chip8::OP_Fx0A() {
    if (keypad.areKeysPressed())
        v[x] = keypad.getFirstKey();
    else
        pc -= 2;
}

void Chip8::OP_Fx15() {
    delayTimer = v[x];
}

void Chip8::OP_Fx18() {
    soundTimer = v[x];
}

void Chip8::OP_Fx1E() {
    i += v[x];
}

void Chip8::OP_Fx29() {
    i = 5 * v[x];
}

void Chip8::OP_Fx33() {
    memory[i] = v[x] / 100; //Hundereds
    memory[i + 1] = (v[x] % 100 ) / 10; //Tens
    memory[i + 2] = v[x] % 10; //Ones
}

void Chip8::OP_Fx55() {
    for (int registerIndex = 0; registerIndex <= x; registerIndex++)
        memory[i + registerIndex] = v[registerIndex];
}

void Chip8::OP_Fx65() {
    for (int registerIndex = 0; registerIndex <= x; registerIndex++)
        v[registerIndex] = memory[i + registerIndex];
}