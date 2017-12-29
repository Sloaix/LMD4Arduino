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
  BitmapConfig config = BitmapConfig::BICOLOR;
  int width;
  int height;
  byte *buffer;
  Bitmap()
  {
  }

public:
  static Bitmap *createBitmap(int width, int height, BitmapConfig config);
  static Bitmap *createBitmap(int width, int height);
  static Bitmap *createBitmap(Bitmap bitmap);
  void copyPixelsFromBuffer(byte buffer[]);
  void copyPixelsToBuffer(byte buffer[]);
  void setConfig(BitmapConfig config);
  int getByteCount();
  int getRowByteCount();
  int getWidth();
  int getHeight();
  byte *getBuffer();
  Bitmap *clone();
  BitmapConfig getConfig();
};

#endif //Bitmap.h