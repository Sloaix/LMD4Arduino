#ifndef Paint_h
#define Paint_h
#include <Arduino.h>

enum Style
{
  FILL,
  CLEAR,
  STROKE,
  OUTTER_STROKE,
  INNER_STORKE
};

class Paint
{
private:
  int color = 0xFF000000; //默认黑色不透明
  int thickness;          //for stroke style
  Style style;

public:
  void setColor(int color);
  int getColor();
  void setStyle(Style style);
  Style getStyle();
  void setThickness(int thickness);
  int getThickness();
};
#endif
