#include "BufferCanvas.h"

BufferCanvas::BufferCanvas(byte *buffer, int width, int height)
{
    Serial.println("宽度");
    Serial.println(this->width);
    Serial.println("高度");
    Serial.println(this->width);

    this->buffer = buffer;
    this->width = width;
    this->height = height;
    this->horizontalUnitSize = width / 8;
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

    // Serial.println(getBufferSize());
    for (int i = 0; i < getBufferSize(); i++)
    {
        Serial.println("test");
        this->buffer[i] = 0xff;
    }
}

int BufferCanvas::getBufferSize()
{
    return this->horizontalUnitSize * this->height;
}