#ifndef Canvas_h
#define Canvas_h

#include <Arduino.h>
#include "Paint.h"

class Canvas
{
private:
public:
  void drawBitmap(Bitmap bitmap, Paint paint);
  void drawLine(int startX, int startY, int stopX, int stopY, Paint paint);
  void drawLines(int points[], Paint paint);
  void drawPoint(int x, int y, Paint paint);
  void draw(Paint paint);
  void reverse();
};
#endif
