#include "Bitmap.h"

static Bitmap *Bitmap::createBitmap(int width, int height, BitmapConfig config)
{
  Bitmap *bitmap = &Bitmap();
  bitmap->width = width;
  bitmap->height = height;
  bitmap->config = config;
  return bitmap;
}

static Bitmap *Bitmap::createBitmap(int width, int height)
{
  return Bitmap::createBitmap(width, height, BitmapConfig::BICOLOR);
}

Bitmap *Bitmap::clone()
{
  Bitmap *bitmap = &Bitmap();
  bitmap->width = this->width;
  bitmap->height = this->height;
  bitmap->config = this->config;
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