#include "Bitmap.h"

static Bitmap *Bitmap::createBitmap(int width, int height, BitmapConfig config)
{
  Bitmap *bitmap = &Bitmap();
  bitmap->width = width;
  bitmap->height = height;
  bitmap->config = config;
  bitmap->buffer = new byte[bitmap->getByteCount()]{0};
  return bitmap;
}

static Bitmap *Bitmap::createBitmap(int width, int height)
{
  return Bitmap::createBitmap(width, height, BitmapConfig::BICOLOR);
}

static Bitmap *Bitmap::createBitmap(Bitmap *bitmap)
{
  return bitmap->clone();
}

Bitmap *Bitmap::clone()
{
  Bitmap *bitmap = &Bitmap();
  bitmap->width = this->width;
  bitmap->height = this->height;
  bitmap->config = this->config;
  memcpy(bitmap->buffer, this->buffer, getByteCount());
  return bitmap;
}

void Bitmap::setConfig(BitmapConfig config)
{
  this->config = config;
}

BitmapConfig Bitmap::getConfig()
{
  return this->config;
}

int Bitmap::getWidth()
{
  return this->width;
}

int Bitmap::getHeight()
{
  return this->height;
}

byte *Bitmap::getBuffer()
{
  return this->buffer;
}

int Bitmap::getRowByteCount()
{
  switch (this->config)
  {
    //一个字节可以存储8位数据,每位代表一列
  case BitmapConfig::BICOLOR:
    return this->width / 8;
    //一个字节存储一个alpha值
  case BitmapConfig::ALPHA_8:
    return this->width;
  default:
    return 0;
  }
  return 0;
}

int Bitmap::getByteCount()
{
  return getRowByteCount() * this->height;
}

void Bitmap::setPixel(int x, int y, int color)
{
  if (x < 0 || x > this->width || y < 0 || y > this->height)
  {
    return;
  }

  switch (this->config)
  {
  case BitmapConfig::BICOLOR:
    setPixelWithBicolor(x, y, color);
    return;
  }
  return;
}

int Bitmap::getPixel(int x, int y)
{
  if (x < 0 || x > this->width || y < 0 || y > this->height)
  {
    return -1;
  }

  switch (this->config)
  {
  case BitmapConfig::BICOLOR:
    return getPixelWithBicolor(x, y);
  }

  return -1;
}

void Bitmap::setPixelWithBicolor(int x, int y, int color)
{
  //处理color,进行二值化
  int bit = color;

  if (bit != 0 || bit != 1)
  {
    bit = bit > 0x7f ? 0 : 1;
  }

  //计算点在字节中的bit位置,从右到左
  int bitIndex = 7 - x % 8;

  //计算字节的处于Buffer中的下标
  int byteIndex = x / 8 + y * this->width / 8;

  //设置对应x,y像素位置的bit
  bitWrite(this->buffer[byteIndex], bitIndex, bit);
}

int Bitmap::getPixelWithBicolor(int x, int y)
{
  //计算点在字节中的bit位置,从右到左
  int bitIndex = 7 - x % 8;

  //计算字节的处于Buffer中的下标
  int byteIndex = x / 8 + y * this->width / 8;

  //读取对应x,y像素位置的bit
  return bitRead(this->buffer[byteIndex], bitIndex);
}