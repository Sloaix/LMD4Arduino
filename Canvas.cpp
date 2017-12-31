#include "Canvas.h"

Canvas::Canvas(Bitmap *bitmap)
{
  this->bitmap = bitmap;

  return;
}

void Canvas::drawPoint(int x, int y, Paint *paint)
{
  switch (paint->getStyle())
  {
  case Style::FILL:
    this->bitmap->setPixel(x, y, paint->getColor());
    break;
  case Style::CLEAR:
    this->bitmap->setPixel(x, y, 0xFF000000);
    break;
  }

  return;
}

void Canvas::drawColor(int color)
{
  for (int x = 0; x < this->bitmap->getWidth(); x++)
  {
    for (int y = 0; y < this->bitmap->getHeight(); y++)
    {
      this->bitmap->setPixel(x, y, color);
    }
  }
}

void Canvas::drawBitmap(Bitmap *bitmap, Paint *paint)
{
  this->bitmap = bitmap->clone();
}

//bresenham算法(未优化版)
void Canvas::drawLine(int startX, int startY, int stopX, int stopY, Paint *paint)
{
  //计dx,dy
  int dx = stopX - startX;
  int dy = stopY - startY;
  int d = 0; //决策值
  int x = startX;
  int y = startY;
  int k = dy / dx;

  while (x != stopX)
  {
    drawPoint(x, y, paint);
    x++;
    if (d > 0.5)
    {
      y = y + 1;
    }

    d += k;

    d = d > 1 ? d - 1 : d;
  }
}

void Canvas::drawRect(int startX, int startY, int width, int height, Paint *paint)
{
}