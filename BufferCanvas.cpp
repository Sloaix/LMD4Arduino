#include "BufferCanvas.h"

BufferCanvas::BufferCanvas(byte *buffer, int bufferSize, int width, int height)
{
    this->buffer = buffer;
    this->bufferSize = bufferSize;
    this->width = width;
    this->height = height;
    this->column = width / 8;
}

static void BufferCanvas::shiftLineRight(byte *buffer, int start, int end, bool circular)
{
    int lowBitOfHeadByte = bitRead(buffer[end], 0); //获取尾字节的最低位bit

    for (int i = end; i >= start; i--)
    {
        buffer[i] >>= 1; //当前字节右移一位
        if (i != start)
        {
            int lowBitOfNextByte = 0;
            lowBitOfNextByte = bitRead(buffer[i - 1], 0); //获取上一个字节的最低位bit
            bitWrite(buffer[i], 7, lowBitOfNextByte);     //把获取到的下一个字节高位覆盖到当前字节的最低位
        }
    }

    bitWrite(buffer[start], 7, lowBitOfHeadByte);
}

static void BufferCanvas::shiftLineLeft(byte *buffer, int start, int end, bool circular)
{
    int highBitOfHeadByte = bitRead(buffer[start], 7); //获取头字节的最高位bit

    for (int i = start; i <= end; i++)
    {
        buffer[i] <<= 1; //当前字节左移一位

        if (i != end)
        {
            int highBitOfNextByte = 0;
            highBitOfNextByte = bitRead(buffer[i + 1], 7); //获取下一个字节的最高位bit
            bitWrite(buffer[i], 0, highBitOfNextByte);     //把获取到的下一个字节高位覆盖到当前字节的最低位
        }
    }

    bitWrite(buffer[end], 0, highBitOfHeadByte);
}

static void BufferCanvas::shiftBufferRight(byte *buffer, int size, int distance, int bytesNumberEachLine, bool circular)
{
    while (distance--)
    {
        for (int i = 0; i < size; i += bytesNumberEachLine)
        {
            int start = 0 + i;
            int end = 7 + i;
            shiftLineRight(buffer, start, end, circular);
        }
    }
}

static void BufferCanvas::shiftBufferLeft(byte *buffer, int size, int distance, int bytesNumberEachLine, bool circular)
{
    while (distance--)
    {
        for (int i = 0; i < size; i += bytesNumberEachLine)
        {
            int start = 0 + i;
            int end = 7 + i;
            shiftLineLeft(buffer, start, end, circular);
        }
    }
}

void BufferCanvas::shiftLeft(int distance, bool circular)
{
    BufferCanvas::shiftBufferLeft(this->buffer, this->bufferSize, distance, this->column, circular);
}

void BufferCanvas::shiftRight(int distance, bool circular)
{
    BufferCanvas::shiftBufferRight(this->buffer, this->bufferSize, distance, this->column, circular);
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
    for (int i = 0; i < this->bufferSize; i++)
    {
        this->buffer[i] = 0x00;
    }
}

void BufferCanvas::full()
{
    for (int i = 0; i < this->bufferSize; i++)
    {
        this->buffer[i] = 0xff;
    }
}

void BufferCanvas::reverse()
{
    for (int i = 0; i < this->bufferSize; i++)
    {
        this->buffer[i] = ~this->buffer[i];
    }
}
bool BufferCanvas::containPixel(int x, int y)
{
    if (x < 0 || x > this->width)
    {
        return false;
    }

    if (x < 0 || y > this->height)
    {
        return false;
    }

    return true;
}

void BufferCanvas::setPixelState(int x, int y, int bit)
{
    //计算点在字节中的bit位置,从右到左
    int bitIndex = 7 - x % 8;

    //计算字节的处于Buffer中的下标
    int byteIndex = x / 8 + y * this->column;

    //设置bit位为1
    bitWrite(this->buffer[byteIndex], bitIndex, bit);
}

void BufferCanvas::drawPixel(int x, int y)
{
    setPixelState(x, y, 1);
}
void BufferCanvas::clearPixel(int x, int y)
{
    setPixelState(x, y, 0);
}

void BufferCanvas::drawHorizontalLine(int startX, int startY, int length)
{
    if (!containPixel(startX, startY))
    {
        return;
    }

    if (length + startX > this->width)
    {
        return;
    }

    for (int i = startX; i < length; i++)
    {
        drawPixel(i, startY);
    }
}

void BufferCanvas::drawLine(int startX, int startY, int endX, int endY)
{
}