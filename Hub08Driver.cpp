#include "Hub08Driver.h"

Hub08Driver::Hub08Driver(int horizontalUnitSize, int pinOE, int pinLA, int pinLB, int pinLC, int pinLD, int pinSTB)
{
    this->horizontalUnitSize = horizontalUnitSize;
    this->pinOE = pinOE;
    this->pinLA = pinLA;
    this->pinLB = pinLB;
    this->pinLC = pinLC;
    this->pinLD = pinLD;
    this->pinSTB = pinSTB;
    this->buffer = new byte[horizontalUnitSize * 16]{0};
    init();
}

void Hub08Driver::init()
{
    // if (this->isDebug)
    // {
    //     Serial.begin(9600);
    // }

    SPI.begin();

    //都设置为输出模式
    pinMode(pinOE, OUTPUT);
    pinMode(pinLA, OUTPUT);
    pinMode(pinLB, OUTPUT);
    pinMode(pinLC, OUTPUT);
    pinMode(pinLD, OUTPUT);
    pinMode(pinSTB, OUTPUT);

    debug("init finish");
}

void Hub08Driver::resetScanLine()
{
    this->scanLineIndex = 0;
}

int Hub08Driver::getBufferSize()
{
    return this->horizontalUnitSize * 16;
}

void Hub08Driver::reverse()
{
    debug("reverse the buffer");
    this->isReverse = !this->isReverse;
}

void Hub08Driver::clear()
{

    for (int i = 0; i < getBufferSize(); i++)
    {
        this->buffer[i] = 0x00;
    }
}

void Hub08Driver::full()
{
    for (int i = 0; i < getBufferSize(); i++)
    {
        this->buffer[i] = 0xff;
    }
}

void Hub08Driver::lockLine()
{
    //拉低，拉高，完成锁存操作
    digitalWrite(this->pinSTB, LOW);
    digitalWrite(this->pinSTB, HIGH);
}

void Hub08Driver::scanLine()
{
    if (!isEnable)
    {
        return;
    }

    switchOff();

    pickLine(this->scanLineIndex);
    pickColumns(this->scanLineIndex);
    lockLine();

    switchOn();

    //换行,范围是0..15
    this->scanLineIndex = (this->scanLineIndex + 1) & 0x0F;
}

void Hub08Driver::pickColumns(int lineIndex)
{
    //遍历每行的小led模块数
    for (int byteIndex = 0; byteIndex < this->horizontalUnitSize; byteIndex++)
    {
        //一个字节的二进制形式可以控制8个led像素点
        byte byteOf8pixels = ~getByteOfLine(lineIndex, byteIndex);

        if (this->isReverse)
        {
            byteOf8pixels = ~byteOf8pixels;
        }
        //写入
        SPI.transfer(byteOf8pixels);
    }
}

byte Hub08Driver::getByteOfLine(int lineIndex, int byteIndex)
{
    return this->buffer[LED_UNIT_SIDE_SIZE * lineIndex + byteIndex];
}

//读取选择的行的二进制对应位的状态
void Hub08Driver::pickLine(int line)
{
    //LA是最低位,LD最高位
    digitalWrite(this->pinLA, bitRead(line, 0));
    digitalWrite(this->pinLB, bitRead(line, 1));
    digitalWrite(this->pinLC, bitRead(line, 2));
    digitalWrite(this->pinLD, bitRead(line, 3));
}

void Hub08Driver::switchOn()
{
    if (this->isEnable)
    {
        return;
    }

    digitalWrite(this->pinOE, LOW);

    this->isEnable = true;
}

void Hub08Driver::switchOff()
{
    if (!this->isEnable)
    {
        return;
    }

    digitalWrite(this->pinOE, HIGH);

    this->isEnable = false;
}

void Hub08Driver::draw(byte *buffer)
{
    memcpy(this->buffer, buffer, getBufferSize());
}

byte *Hub08Driver::getBuffer()
{
    return this->buffer;
}

void Hub08Driver::debug(String content)
{
    if (!this->isDebug)
    {
        return;
    }

    Serial.println(content);
}