#ifndef Canvas_h
#define Canvas_h

#include <Arduino.h>
#include "Bitmap.h"
#include "Paint.h"

class Canvas
{
private:
  Bitmap *bitmap;

public:
  Canvas(Bitmap *bitmap);
  void drawPoint(int x, int y, Paint *paint);
  void drawColor(int color);
  void drawRect(int startX, int startY, int width, int height, Paint *paint);
  void drawLine(int startX, int startY, int stopX, int stopY, Paint *paint);
  void drawLines(int points[], Paint *paint);
  void drawBitmap(Bitmap *bitmap, Paint *paint);
  void reverse();
};
#endif
