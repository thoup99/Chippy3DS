#include "cpu.h"

void Cpu::loadFont() {
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

void Cpu::loadROM() {
        FILE *file = fopen("romfs:/SPACE-INVADER.ch8", "rb");
        
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

void Cpu::cycle() {
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
    }

    playSound();
    renderer.render();
}

void Cpu::executeInstruction() {
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


void Cpu::updateTimers() {
    if (delayTimer > 0)
        delayTimer -= 1;

    if (soundTimer > 0)
        soundTimer -= 1;
}

void Cpu::playSound() {

}



u8 Cpu::getRandomByte() {
    return rand() % 255 + 1;
}

void Cpu::OP_00E0() {
    renderer.clear();
}

void Cpu::OP_00EE()//
{
    stkpt--;
    pc = stack[stkpt];
}

void Cpu::OP_1nnn()
{
    pc = (opcode & 0xFFF);
}

void Cpu::OP_2nnn() //
{
    stack[stkpt] = pc;
    stkpt++;

    pc = (opcode & 0xFFF);
}

void Cpu::OP_3xkk() {
    if (v[x] == (opcode & 0xFF))
        pc += 2;
}

void Cpu::OP_4xkk() {
    if (v[x] != (opcode & 0xFF))
        pc += 2;
}

void Cpu::OP_5xy0() {
    if (v[x] == v[y])
        pc += 2;
}

void Cpu::OP_6xkk()
{
    v[x] = (opcode & 0xFF);
}

void Cpu::OP_7xkk()
{
    v[x] += (opcode & 0xFF);
}

void Cpu::OP_8xy0() {
    v[x] = v[y];
}

void Cpu::OP_8xy1(){
    v[x] |= v[y];
}

void Cpu::OP_8xy2() {
    v[x] &= v[y];
}

void Cpu::OP_8xy3() {
    v[x] ^= v[y];
}

void Cpu::OP_8xy4() {
    u16 sum = v[x] + v[y];

    v[0xF] = 0;

    if (sum > 0xFF)
        v[0xF] = 1;

    v[x] = sum & 0xFF;
}

void Cpu::OP_8xy5() {
    v[0xF] = 0;

    if (v[x] > v[y])
        v[0xF] = 1;

    v[x] -= v[y];
}

void Cpu::OP_8xy6() {
    v[0xF] = (v[x] & 0x1);

    v[x] >>= 1;
}

void Cpu::OP_8xy7() {
    v[0xF] = 0;       

    if (v[y] > v[x])
        v[0xF] = 1;

    v[x] = v[y] - v[x];
}

void Cpu::OP_8xyE() {
    v[0xF] = (v[x] & 0x80);
    v[x] <<= 1;
}

void Cpu::OP_9xy0() {
    if (v[x] != v[y])
        pc += 2;
}

void Cpu::OP_Annn()
{
    i = (opcode & 0xFFF);
}

void Cpu::OP_Bnnn() {
    pc = (opcode & 0xFFF) + v[0x0];
}

void Cpu::OP_Cxkk() {
    u8 byte = opcode & 0xFF;
    v[x] = getRandomByte() & byte;
}

void Cpu::OP_Dxyn()
{
    int width = 8;
    int height = (opcode & 0xF);

    v[0xF] = 0;

    for (int row = 0; row < height; row++)
    {
        u8 sprite = memory[i + row];

        for (int col = 0; col < width; col++)
        {
            if ((sprite & 0x80) > 0)
            {
                
                if (renderer.setPixel(v[x] + col, v[y] + row))
                    v[0xF] = 1;
            }

            sprite <<= 1;
        }        
    }
}

void Cpu::OP_Ex9E() {
    if (keypad.isKeyPressed(v[x]))
        pc += 2;
}

void Cpu::OP_ExA1(){
    if (!keypad.isKeyPressed(v[x]))
        pc += 2;
}

void Cpu::OP_Fx07() {
    v[x] = delayTimer;
}

void Cpu::OP_Fx0A() {
    if (keypad.areKeysPressed())
        v[x] = keypad.getFirstKey();
    else
        pc -= 2;
}

void Cpu::OP_Fx15() {
    delayTimer = v[x];
}

void Cpu::OP_Fx18() {
    soundTimer = v[x];
}

void Cpu::OP_Fx1E() {
    i += v[x];
}

void Cpu::OP_Fx29() {
    i = 5 * v[x];
}

void Cpu::OP_Fx33() {
    memory[i] = v[x] / 100; //Hundereds
    memory[i + 1] = (v[x] % 100 ) / 10; //Tens
    memory[i + 2] = v[x] % 10; //Ones
}

void Cpu::OP_Fx55() {
    for (int registerIndex = 0; registerIndex <= x; registerIndex++)
        memory[i + registerIndex] = v[registerIndex];
}

void Cpu::OP_Fx65() {
    for (int registerIndex = 0; registerIndex <= x; registerIndex++)
        v[registerIndex] = memory[i + registerIndex];
}