#include "BufferCanvas.h"

BufferCanvas::BufferCanvas(byte *buffer, int width, int height)
{
    this->buffer = buffer;
    this->width = width;
    this->height = height;
    this->horizontalUnitSize = width / 8;
}

void BufferCanvas::shiftLeft(int distance, bool circular)
{
    for (int i = 0; i < 16; i++)
    {
        int start = 0 + 8 * i;
        int end = 7 + 8 * i;
        shiftLeftByteArray(start, end, circular);
    }
}

void BufferCanvas::shiftRight(int distance, bool circular)
{
    for (int i = 0; i < 16; i++)
    {
        int start = 0 + 8 * i;
        int end = 7 + 8 * i;
        shiftRightByteArray(start, end, circular);
    }
}

void BufferCanvas::shiftLeftByteArray(int start, int end, bool circular)
{
    int highBitOfHeadByte = (this->buffer[start] & 0x80) == 0x80 ? 1 : 0; //获取头字节的最高位bit

    for (int i = start; i <= end; i++)
    {
        int highBitOfNextByte = 0;

        if (i != end)
        {
            highBitOfNextByte = (this->buffer[i + 1] & 0x80) == 0x80 ? 1 : 0; //获取下一个字节的最高位bit
        }

        this->buffer[i] <<= 1; //当前字节左移一位

        this->buffer[i] |= highBitOfNextByte; //把获取到的下一个字节高位覆盖到当前字节的最低位

        //当遍历到最后一个字节时候
        if (circular && i == end)
        {
            this->buffer[i] |= highBitOfHeadByte; //将头字节的最高位，放入移位后的尾字节的最低位
        }
    }
}

void BufferCanvas::shiftRightByteArray(int start, int end, bool circular)
{
    byte *bytes = this->buffer;
    int lowBitOfEndByte = (bytes[end] & 0x01) == 0x01 ? 1 : 0; //获取尾字节的最低位bit

    for (int i = end; i >= start; i--)
    {

        int lowBitOfNextByte = 0;

        if (i - 1 >= start)
        {
            lowBitOfNextByte = (bytes[i - 1] & 0x01) == 0x01 ? 1 : 0; //获取下一个字节的最低位
        }

        bytes[i] >>= 1; //当前字节右移一位

        //把获取到的下一个字节低位覆盖到当前字节的最高位
        bytes[i] ^= (-lowBitOfNextByte ^ bytes[i]) & (1UL << 7);

        //当遍历到最后一个字节时候
        if (circular && i == start)
        {
            bytes[start] ^= (-lowBitOfEndByte ^ bytes[start]) & (1UL << 7); //将尾字节的最低位，放入移位后的头字节的最高位
        }
    }
}

int BufferCanvas::getWidth()
{
    return this->width;
}

int BufferCanvas::getHeight()
{
    return this->height;
}

void BufferCanvas::clear()
{
    for (int i = 0; i < getBufferSize(); i++)
    {
        this->buffer[i] = 0x00;
    }
}

void BufferCanvas::full()
{
    for (int i = 0; i < getBufferSize(); i++)
    {
        this->buffer[i] = 0xff;
    }
}

int BufferCanvas::getBufferSize()
{
    return this->horizontalUnitSize * this->height;
}

int BufferCanvas::getHorizontalUnitSize()
{
    return this->horizontalUnitSize;
}

void BufferCanvas::reverse()
{
    for (int i = 0; i < getBufferSize(); i++)
    {
        this->buffer[i] = ~this->buffer[i];
    }
}

void BufferCanvas::drawLine(int startX, int startY, int endX, int endY)
{
}