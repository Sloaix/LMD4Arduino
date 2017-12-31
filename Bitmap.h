#ifndef Bitmap_h
#define Bitmap_h

#include <Arduino.h>

enum BitmapConfig
{
  BICOLOR,
  ALPHA_8
};
class Bitmap
{
private:
  int width;
  int height;
  BitmapConfig config = BitmapConfig::BICOLOR;
  byte *buffer;
  void setPixelWithBicolor(int x, int y, int color);
  int getPixelWithBicolor(int x, int y);

public:
  static Bitmap *createBitmap(int width, int height, BitmapConfig config);
  static Bitmap *createBitmap(int width, int height);
  static Bitmap *createBitmap(Bitmap *bitmap);
  void copyPixelsFromBuffer(byte *buffer, BitmapConfig config);
  void copyPixelsToBuffer(byte *buffer, BitmapConfig config);
  void setConfig(BitmapConfig config);    //设置配置
  void setPixel(int x, int y, int color); //设置某一个像素的颜色
  int getPixel(int x, int y);             //返回指定像素的颜色
  int getByteCount();                     //整个Bitmap的字节个数
  int getRowByteCount();                  //每行的字节个数
  int getWidth();                         //Bitmap宽度
  int getHeight();                        //Bitmap高度
  byte *getBuffer();                      //Bitmap内容存储Buffer
  Bitmap *clone();                        //返回一个Bitmap的深度拷贝
  BitmapConfig getConfig();               //返回BitmapConfig
  ~Bitmap()
  {
    delete this->buffer;
    this->buffer = NULL;
  }
};

#endif //Bitmap.h