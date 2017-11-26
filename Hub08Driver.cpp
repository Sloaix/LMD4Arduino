#include "Hub08Driver.h"

Hub08Driver::Hub08Driver(int horizontalUnitCascadeSize, byte *buffer, int pinOE, int pinLA, int pinLB, int pinLC, int pinLD, int pinSTB)
{
    this->horizontalUnitCascadeSize = horizontalUnitCascadeSize;
    this->buffer = buffer;
    this->pinOE = pinOE;
    this->pinLA = pinLA;
    this->pinLB = pinLB;
    this->pinLC = pinLC;
    this->pinLD = pinLD;
    this->pinSTB = pinSTB;
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

void Hub08Driver::reverse()
{
    debug("reverse the buffer");
    this->isReverse = !this->isReverse;
}

void Hub08Driver::clear()
{
    byte off = 0x00;
    for (int i = 0; i < sizeof(this->buffer); i++)
    {
        this->buffer[i] = off;
    }
}

void Hub08Driver::full()
{
    byte on = 0xff;
    for (int i = 0; i < sizeof(this->buffer); i++)
    {
        this->buffer[i] = on;
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
    for (int byteIndex = 0; byteIndex < this->horizontalUnitCascadeSize; byteIndex++)
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
    digitalWrite(this->pinLA, line & 0x01);
    digitalWrite(this->pinLB, line & 0x02);
    digitalWrite(this->pinLC, line & 0x04);
    digitalWrite(this->pinLD, line & 0x08);
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

void Hub08Driver::setBuffer(byte *buffer)
{
    this->buffer = buffer;
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