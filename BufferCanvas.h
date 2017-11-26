#ifndef BufferCanvas_h
#define BufferCanvas_h

#include <Arduino.h>

/**
 * BufferCanvas，可以在指定宽高的Buffer上使用更多方法绘制1bit位图
 */
class BufferCanvas
{
private:
  byte *buffer;

  void init();

public:
  BufferCanvas(byte *buffer, int width, int height);
};

#endif //BufferCanvas.h
