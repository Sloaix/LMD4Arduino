#ifndef Paint_h
#define Paint_h
#include <Arduino.h>

enum Style
{
  FILL,
  CLEAR,
  OUTTER_STROKE,
  INNER_STORKE
};

class Paint
{
private:
  int thickness; //for stroke style
  Style style;

public:
  void setStyle(Style style);
  Style getStyle();
  void setThickness(int thickness);
  int getThickness();
};
#endif
